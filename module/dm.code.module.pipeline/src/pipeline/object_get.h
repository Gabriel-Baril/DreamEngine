#pragma once

#include "core/core.h"

#include "cache.h"
#include "signature.h"

namespace dm
{
	enum class ObjectRequestResult
	{
		SUCCESS,
		NOT_FOUND
	};

	template <typename T>
	const void *object_touch(const Signature<T> &sig)
	{
		const u64 objectId = object_get_id(sig);

		if (const void *object = cache_obj_load(objectId))
		{
			return object;
		}

		// If fetching fails for some reasons that's ok. Multiple causes are possible.
		// Object not in the cache, one dependency of the object was invalidated, etc
		const ObjectRequestResult requestResult = object_request(sig);
		if (!request_success(requestResult))
		{
			object_request_failure(sig, requestResult);
			return nullptr;
		}

		const void *object = cache_obj_load(objectId);
		if (!object)
		{
			object_load_failure(sig);
			return nullptr;
		}

		return object;
	}

	template <typename T>
	struct Handle
	{
		using Underlying = typename T::Underlying;

		Handle(obj_t id)
				: objectId{id}
		{
		}

		Handle()
				: objectId{}
		{
		}

		bool valid() const
		{
			return objectId != NULL_OBJ;
		}

		const Underlying *get()
		{
			const Underlying *object = flatbuffers::GetRoot<Underlying>(cache_obj_load(objectId));
			if (object)
			{
				return object;
			}
			Signature<T> *sig = (Signature<T> *)signature_get(objectId);
			if (!sig)
			{
				return nullptr;
			}
			return flatbuffers::GetRoot<Underlying>(object_touch<T>(*sig));
		}

		const Underlying *operator->()
		{
			return get();
		}

		~Handle()
		{
			// cache_obj_unload(objectId);
		}

		obj_t objectId = NULL_OBJ;
	};

	bool request_success(ObjectRequestResult result);

	template <typename T>
	Handle<T> object_get(const Signature<T> &sig)
	{
		(void *)object_touch(sig);
		const u64 objectId = object_get_id(sig);
		return Handle<T>{objectId};
	}
}
