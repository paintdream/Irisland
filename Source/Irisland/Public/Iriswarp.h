/*
The Iris Concurrency Framework

This software is a Unreal Engine Plugin of iris library.

The MIT License (MIT)

Copyright (c) 2023 PaintDream

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once
#include "CoreMinimal.h"
#include "Irisland.h"

struct IRISLAND_API FIriswarp : public iris::iris_warp_t<FIrisland, false, TFunction<void()>>
{
public:
	using FWarp = iris::iris_warp_t<FIrisland, false, TFunction<void()>>;
	FIriswarp();

	// forward APIs
	template <typename F>
	void QueueRoutine(F&& func)
	{
		FWarp::queue_routine(std::forward<F>(func));
	}

	template <typename F>
	void QueueRoutinePost(F&& func)
	{
		FWarp::queue_routine_post(std::forward<F>(func));
	}

	template <typename F>
	void QueueRoutineExternal(F&& func)
	{
		FWarp::queue_routine_external(std::forward<F>(func));
	}

	void QueueBarrier()
	{
		FWarp::queue_barrier();
	}

	void Suspend() noexcept
	{
		FWarp::suspend();
	}

	void Resume() noexcept
	{
		FWarp::resume();
	}

	void Join()
	{
		FWarp::join();
	}

	bool IsEmpty() const noexcept
	{
		return FWarp::empty();
	}

	bool IsSuspended() const noexcept
	{
		return FWarp::is_suspended();
	}

	FIrisland& GetAsyncWorker() noexcept
	{
		return FWarp::get_async_worker();
	}

	static FIriswarp* GetCurrent() noexcept
	{
		return static_cast<FIriswarp*>(FWarp::get_current_warp());
	}
};