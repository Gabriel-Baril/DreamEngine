#pragma once

namespace dm
{
	template <typename T>
	struct Request
	{
	};

	template <typename T>
	struct Response
	{
	};

	enum class ResponseStatus
	{
		SUCCESS,
		FAILED,
	};

	template <typename T>
	void request_send(const Request<T>& req, Response<T>& res)
	{
		request_handle(req, res);
	}

	// TODO: request_send_async
}
