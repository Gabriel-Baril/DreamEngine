#pragma once

#include "pipeline/request.h"
#include "pipeline/signature.h"
#include "pipeline/object_get.h"
#include "pipeline/symdb.h"
#include "pipeline/cache.h"
#include "pipeline/xsrc_request.h"

namespace dm
{
#define DEFINE_XASSET_READ_CONSTRUCTORS(XAssetObjectType)							\
	Request(sym_t sym) : sig{ make_signature<XAssetObjectType>(sym) } {}			

#define XASSET_OBJECT_API(XAssetObjectType)																												\
    template <> struct Signature<XAssetObjectType> {																									\
        Signature() = default;																															\
        Signature(sym_t _symbol) : symbol(_symbol) {}																									\
        sym_t symbol{};																																	\
    };																																					\
    DM_INLINE u64 object_get_id(const Signature<XAssetObjectType>& sig) { return xasset_object_signature_build_id(sig); }									\
    DM_INLINE i32 object_get_slug(const Signature<XAssetObjectType>& sig, char* buffer, u64 count) { return object_get_slug_generic(sig, buffer, count); }	\
    DM_INLINE ObjectRequestResult object_request(const Signature<XAssetObjectType>& sig) { return xsrc_object_request(sig.symbol, object_get_id(sig)); }  	\
    DM_INLINE void object_request_failure(const Signature<XAssetObjectType>& sig, ObjectRequestResult r){ object_request_failure_generic(sig, r); }       	\
    DM_INLINE void object_load_failure(const Signature<XAssetObjectType>& sig) { object_load_failure_generic(sig); }

#define XASSET_READ_API(XAssetObjectType)																															\
	template <>																																						\
	struct Request<XAssetObjectType>																																\
	{																																								\
		Request() = default;																																		\
		void set_symbol(sym_t sym) { sig = make_signature<typename XAssetObjectType::UnderlyingObject>(sym); }												\
		Signature<typename XAssetObjectType::UnderlyingObject> sig{};																								\
	};																																								\
	template <>																																						\
	struct Response<XAssetObjectType>																																\
	{																																								\
		Handle<typename XAssetObjectType::UnderlyingObject> data;																									\
	};																																								\
	DM_INLINE void request_handle(const Request<XAssetObjectType>& req, Response<XAssetObjectType>& res) { res = xasset_read_request_handle_generic<XAssetObjectType>(req); }	\
	DM_INLINE const char* requet_get_type_name(const Request<XAssetObjectType>& req) { DM_MAYBE_UNUSED(req); return DM_NAMEOF(XAssetObjectType); }						\
	DM_INLINE bool request_valid(const Request<XAssetObjectType>& req) { DM_MAYBE_UNUSED(req); return true; }															\
	DM_INLINE u64 request_get_id(const Request<XAssetObjectType>& req) { return xasset_read_request_build_id(req); }													\
	DM_INLINE i32 request_get_slug(const Request<XAssetObjectType>& req, char* buffer, u64 count) { return request_get_generic_xasset_slug(req, buffer, count); }		\
	DM_INLINE ResponseStatus response_success(const Response<XAssetObjectType>& res) { return res.data.valid() ? ResponseStatus::SUCCESS : ResponseStatus::FAILED; }


	template <typename T>
	struct is_signature : std::false_type
	{
	};

	template <typename U>
	struct is_signature<Signature<U>> : std::true_type
	{
	};

	template <typename T>
	concept HasSignatureMember = requires(const T& t)
	{
		t.sig; // member exists
		requires is_signature<std::remove_cvref_t<decltype(t.sig)>>::value;
	};

	template <typename T>
		requires HasSignatureMember<Request<T>>
	static i32 request_get_generic_xasset_slug(const Request<T>& req, char* buffer, u64 count)
	{
		char objectSlugBuffer[512];
		object_get_slug(req.sig, objectSlugBuffer, DM_ARRLEN(objectSlugBuffer));
		return core_snprintf(buffer, count, "%s(object=%s) [reqid=%zu]", requet_get_type_name(req), objectSlugBuffer, request_get_id(req));
	}

	template<typename T>
	u64 xasset_object_signature_build_id(const Signature<T>& sig)
	{
		HashBuilder hb;
		hb.add_type<T>();
		hb.add(T::VERSION);
		hb.add(static_cast<u64>(sig.symbol));
		return hb.get();
	}

	template<typename T>
	i32 object_get_slug_generic(const Signature<T>& sig, char* buffer, u64 count)
	{
		const SymbolMetadata* meta = symdb_get_meta(sig.symbol);
		if (!meta)
		{
			DM_ERROR_LOG("Symbol not found");
			return core_snprintf(buffer, count, "[%zu, v%zu]", sig.symbol, T::VERSION);
		}
		return core_snprintf(buffer, count, "[%s, v%zu]", meta->name, T::VERSION);
	}


	template <typename T>
	void object_request_failure_generic(const Signature<T>& sig, ObjectRequestResult result)
	{
		DM_MAYBE_UNUSED(result);

		char slug[512];
		object_get_slug(sig, slug, DM_ARRLEN(slug));
		DM_ERROR_LOG("Failed to request object '{0}'", slug);
	}

	template <typename T>
	void object_load_failure_generic(const Signature<T>& sig)
	{
		char slug[512];
		object_get_slug(sig, slug, DM_ARRLEN(slug));
		DM_ERROR_LOG("Failed to load object '{0}'", slug);
	}

	template<typename T>
	u64 xasset_read_request_build_id(const Request<T>& req)
	{
		HashBuilder hb;
		hb.add_type<T>();
		hb.add(T::VERSION);
		hb.add(object_get_id(req.sig));
		return hb.get();
	}

	template <typename T> requires HasSignatureMember<Request<T>>
	Response<T> xasset_read_request_handle_generic(const Request<T>& req)
	{
		Response<T> res;
		res.data = object_get(req.sig);
		return res;
	}
}
