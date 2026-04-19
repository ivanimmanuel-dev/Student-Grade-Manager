/*==========================================================================================
 *									UNIT TESTS
 *							Author: Inderpreet Kaur Hundal
 *==========================================================================================*/

#include "pch.h"
#include "CppUnitTest.h"
#include "../student.h"
#include "../menu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestDriver
{
	TEST_CLASS(add_student)
	{
	public:

		// Normal Cases
		TEST_METHOD(AddStudent_normal)													// add one student
		{ 
			StudentDB db;
			db_init(&db);
			Assert::AreEqual(1, db_addStudent(&db, 0001, "Sehejpreet"));
		}
		TEST_METHOD(Addstudent_morethanone)												// add more than one student
		{
			StudentDB db;
			db_init(&db);
			Assert::AreEqual(1, db_addStudent(&db, 0001, "Sehejpreet"));
			Assert::AreEqual(1, db_addStudent(&db, 0002, "Prabhpreet"));
			Assert::AreEqual(2, db.count);
		}
		TEST_METHOD(addstudent_checkifcorrect)											// check if the entered data is stored correctly
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			Assert::AreEqual(0, strcmp(db.students[0].name,"Sehejpreet"));
		}

		// Edge cases
		TEST_METHOD(Addstudent_gradezero)												// grades of newly added student should be zero
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			Assert::AreEqual(0,db.students[0].gradeCount);
		}
		TEST_METHOD(Addstudent_avgzero)													// average of new student should be zero
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			Assert::AreEqual(0.0f, db.students[0].average, 0.001f);
		}

		//Invalid cases
		TEST_METHOD(Addstudent_duplicateid)												// no two students can have same IDs
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			Assert::AreEqual(INVALID_VALUE, db_addStudent(&db, 0001, "Prabhpreet"));
		}
		TEST_METHOD(Addstudent_negativeid)												// no student can have negative id
		{
			StudentDB db;
			db_init(&db);
			Assert::AreEqual(INVALID_VALUE, db_addStudent(&db,-1, "Sehejpreet"));
		}
		TEST_METHOD(addStudent_zeroid)													// no student can have zero as their id
		{
			StudentDB db;
			db_init(&db);
			Assert::AreEqual(INVALID_VALUE, db_addStudent(&db, 0, "Sehejpreet"));
		}
	};

	TEST_CLASS(RemoveStudentTests)
	{
	public:

		// Normal Cases
		TEST_METHOD(RemoveStudent_Normal)												// remove student
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			Assert::AreEqual(1, db_removeStudent(&db, 0001));
		}
		TEST_METHOD(RemoveStudent_CountDecrease)										// after removal the student count should decrease by 1
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			db_addStudent(&db, 0002, "Prabhpreet");
			db_removeStudent(&db, 0001);
			Assert::AreEqual(1, db.count);
		}
		TEST_METHOD(RemoveStudent_RemainingStudentShiftedCorrectly)						// after removing the first student the second should shift to index 0
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			db_addStudent(&db, 0002, "Prabhpreet");
			db_removeStudent(&db, 0001);
			Assert::AreEqual(0002, db.students[0].id);
		}

		// Edge Cases
		TEST_METHOD(RemoveStudent_LastStudent_CountBecomesZero)							// removing the only student should result in count = 0
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			db_removeStudent(&db, 0001);
			Assert::AreEqual(0, db.count);
		}

		// Invalid Input Cases
		TEST_METHOD(RemoveStudent_NotFound_ReturnsInvalid)								// removing the student which is not in the list will return invalid
		{
			StudentDB db;
			db_init(&db);
			Assert::AreEqual(INVALID_VALUE, db_removeStudent(&db, 9999));
		}
		TEST_METHOD(RemoveStudent_EmptyDatabase_ReturnsInvalid)							// student cannot be removed from empty list
		{
            StudentDB db;
			db_init(&db);
			Assert::AreEqual(INVALID_VALUE, db_removeStudent(&db, 0001));
		}
	};

	TEST_CLASS(RecordGradeTests)
	{
	public:

		// Normal Cases
		TEST_METHOD(RecordGrade_Normal)													// grades added 
		{
            StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			Assert::AreEqual(1, db_recordGrade(&db, 0001, 85.0f));
		}
		TEST_METHOD(RecordGrade_GradeCountIncrease)										// when grades are added count should increase by 1
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			db_recordGrade(&db, 0001, 85.0f);
			Assert::AreEqual(1, db.students[0].gradeCount);
		}
		TEST_METHOD(RecordGrade_Average)												// calculate average
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			db_recordGrade(&db, 0001, 80.0f);
			db_recordGrade(&db, 0001, 90.0f);
			Assert::AreEqual(85.0f, db.students[0].average, 0.001f);
		}

		// Edge Cases
		TEST_METHOD(RecordGrade_MinGrade)												// 0 is the minimum marks
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 1001, "Sehejpreet");
			Assert::AreEqual(1, db_recordGrade(&db, 0001, 0.0f));
		}

		TEST_METHOD(RecordGrade_MaxGrade)												// 100 is the maximum marks
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Alice Smith");
			Assert::AreEqual(1, db_recordGrade(&db, 0001, 100.0f));
		}

		// Invalid Input Cases
		TEST_METHOD(RecordGrade_StudentNotFound)										// grades for a student who is not in the data cannot be added
		{ 
			StudentDB db;
			db_init(&db);
			Assert::AreEqual(INVALID_VALUE, db_recordGrade(&db, 9999, 85.0f));
		}
		TEST_METHOD(RecordGrade_NegativeGrade)											//grades cannot be negative
		{
			StudentDB db; db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			Assert::AreEqual(INVALID_VALUE, db_recordGrade(&db, 1001, -1.0f));
		}
		TEST_METHOD(RecordGrade_GradeAbove100)											// grades cannot be beyong 100
		{
			StudentDB db;
			db_init(&db);
			db_addStudent(&db, 0001, "Sehejpreet");
			Assert::AreEqual(INVALID_VALUE, db_recordGrade(&db, 0001, 101.0f));
		}
	};

	TEST_CLASS(CalcAverageTests)
	{
	public:
		
		// Normal Cases
		TEST_METHOD(CalcAverage_NormalCase)												// average of 80, 90 and 70 should be 80
		{
			float grades[] = { 80.0f, 90.0f, 70.0f };
			Assert::AreEqual(80.0f, db_Average(grades, 3), 0.001f);
		}
		TEST_METHOD(CalcAverage_SingleGrade)											// average of a single grade should be the grade itself
		{
			float grades[] = { 95.0f };
			Assert::AreEqual(95.0f, db_Average(grades, 1), 0.001f);
		}
		TEST_METHOD(CalcAverage_AllSameGrade)											// Average of identical grades should equal that grade
		{
			float grades[] = { 75.0f, 75.0f, 75.0f };
			Assert::AreEqual(75.0f, db_Average(grades, 3), 0.001f);
		}

		//Edge Cases
		TEST_METHOD(CalcAverage_AllZeros)												// Average of all zeros should be 0
		{
			float grades[] = { 0.0f, 0.0f, 0.0f };
			Assert::AreEqual(0.0f, db_Average(grades, 3), 0.001f);
		}
		TEST_METHOD(CalcAverage_All100)													// Average of all 100s should be 100
		{
			float grades[] = { 100.0f, 100.0f, 100.0f };
			Assert::AreEqual(100.0f, db_Average(grades, 3), 0.001f);
		}

		//Invalid Input Cases
		TEST_METHOD(CalcAverage_ZeroCount)												// Count of 0 is invalid
		{
			float grades[] = { 80.0f };
			Assert::AreEqual((float)INVALID_VALUE, db_Average(grades, 0), 0.001f);
		}
		TEST_METHOD(CalcAverage_NegativeCount)											// Negative count is invalid
		{
			float grades[] = { 80.0f };
			Assert::AreEqual((float)INVALID_VALUE, db_Average(grades, -1), 0.001f);
		}
		TEST_METHOD(CalcAverage_NullGrades)												// Null pointer for grades array is invalid
		{
			Assert::AreEqual((float)INVALID_VALUE, db_Average(NULL, 3), 0.001f);
		}
	};

}
