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
#include "Async/Fundamental/Scheduler.h"

#define IRIS_SHARED_LIBRARY_DECORATOR IRISLAND_API
#include "iris/iris_dispatcher.h"

struct FIrisland
{
	static IRISLAND_API FIrisland& Get() noexcept;
	FIrisland() noexcept;
	IRISLAND_API void Queue(TFunction<void()>&& func, size_t priority);

	// APIs for iris library async_worker_t protocol
	IRISLAND_API size_t get_thread_count() const noexcept;
	IRISLAND_API size_t get_current_thread_index() noexcept;
	IRISLAND_API bool is_terminated() const noexcept;

	struct task_t
	{
		task_t(TFunction<void()>&& f, size_t prior) noexcept : func(std::move(f)) {}

		TFunction<void()> func;
		task_t* next = nullptr;
	};

	template <typename F>
	task_t* new_task(F&& func)
	{
		return new task_t(std::forward<F>(func), priority);
	}

	template <typename F>
	void queue(F&& func, size_t priority = 0)
	{
		Queue(std::forward<F>(func), priority);
	}

	void queue_task(task_t* task, size_t priority = 0)
	{
		Queue(std::move(task->func), priority);
		delete task;
	}

	void execute_task(task_t* task) {
		task->func();
		delete task;
	}

private:
	friend struct FThreadIndexer;
	std::atomic<size_t> ThreadIndexCounter { 0 };
};