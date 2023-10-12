#include "pch.h"
#include "CppUnitTest.h"
#include "src/OS/KernelTask.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace CDOSTests
{
	bool func_executed = false;

	TaskExecutionResult test_func()
	{
		func_executed = true;
		return {TaskExecutionResult::COMPLETE};
	}


	TEST_CLASS(KTaskTests)
	{
	public:
		TEST_METHOD(TaskCallsCustomFunctionWhenExecuted)
		{
			KernelTask task = KernelTask(test_func, false, 0);
			auto result = task.execute();
			Assert::IsTrue(func_executed);
		}
	};
}
