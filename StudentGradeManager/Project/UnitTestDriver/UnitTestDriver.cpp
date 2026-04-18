#include "pch.h"
#include "CppUnitTest.h"
#include "../main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestDriver
{
	TEST_CLASS(UnitTestDriver)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(dummyFunction(3, 5), 8);
			Assert::AreEqual(dummyFunction(2, 4), 6);
		}
	};
}
