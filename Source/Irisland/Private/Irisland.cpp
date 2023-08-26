#include "Irisland.h"
#include "Async/Fundamental/Scheduler.h"
#include "Async/Fundamental/Task.h"
#ifdef TEXT
#undef TEXT
#endif
#include "iris/iris_common.inl"

FIrisland::FIrisland() noexcept
{}

FIrisland& FIrisland::Get() noexcept
{
	static FIrisland Instance;
	return Instance;
}

void FIrisland::Queue(TFunction<void()>&& func, size_t priority)
{
	LowLevelTasks::ETaskPriority converted = LowLevelTasks::ETaskPriority::BackgroundLow;
	if (priority < static_cast<size_t>(LowLevelTasks::ETaskPriority::Count))
	{
		converted = static_cast<LowLevelTasks::ETaskPriority>(priority);
	}

	UE::Tasks::Launch(UE_SOURCE_LOCATION, std::move(func), converted);
}

size_t FIrisland::get_thread_count() const noexcept
{
	return LowLevelTasks::FScheduler::Get().GetNumWorkers();
}

bool FIrisland::is_terminated() const noexcept
{
	return get_thread_count() == 0;
}

struct FThreadIndexer
{
	FThreadIndexer() noexcept
	{
		FIrisland& instance = FIrisland::Get();
		index = instance.ThreadIndexCounter.fetch_add(1, std::memory_order_relaxed) % instance.get_thread_count();
	}

	operator size_t()
	{
		return index;
	}

	size_t index;
};

size_t FIrisland::get_current_thread_index() noexcept
{
	if (LowLevelTasks::FScheduler::Get().IsWorkerThread())
	{
		static thread_local FThreadIndexer CurrentThreadIndex;
		return CurrentThreadIndex;
	}
	else
	{
		return ~(size_t)0;
	}
}

