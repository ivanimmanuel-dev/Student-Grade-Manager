#include <stdio.h>
#include <string.h>

void db_init(StudentDB* db)
{
    db->count = 0;
}

int db_idExists(const StudentDB* db, int id)
{
    for (int i = 0; i < db->count; i++)
    {
        if (db->students[i].id == id)
        {
            return 1;
        }
    }
    return 0;
}

int db_addStudent(StudentDB* db, int id, const char* name)
{
    if (db->count >= MAX_STUDENTS)
    {
        return INVALID_VALUE;
    }
    if (id <= 0)
    {
        return INVALID_VALUE;
    }
    if (name == NULL || name[0] == '\0')
    {
        return INVALID_VALUE;
    }
    if (db_idExists(db, id))
    {
        return INVALID_VALUE;
    }
    Student* s = &db->students[db->count];
    s->id = id;
    s->gradeCount = 0;
    s->average = 0;
    strncpy_s(s->name, name, MAX_NAME_LEN - 1);
    s->name[MAX_NAME_LEN - 1] = '\0';
    db->count++;
    return 1;
}

int db_removeStudent(StudentDB* db, int id)
{
    int index = db_findById(db, id);
    if (index == INVALID_VALUE)
    {
        return INVALID_VALUE;
    }
    for (int i = index; i < db->count - 1; i++)
    {
        db->students[i] = db->students[i + 1];
    }
    db->count--;
    return 1;
}

int db_recordGrade(StudentDB* db, int id, float grade)
{
    if (grade < 0 || grade > 100)
    {
        return INVALID_VALUE;
    }
    int index = db_findById(db, id);
    if (index == INVALID_VALUE)
    {
        return INVALID_VALUE;
    }
    Student* s = &db->students[index];
    if (s->gradeCount >= MAX_GRADES)
    {
        return INVALID_VALUE;
    }
    s->grades[s->gradeCount++] = grade;
    s->gradeCount++;
    s->average = db_calcAverage(s->grades, s->gradeCount);
    return 1;

float db_calcAverage(const float grades[], int count)
{
    if (grades == NULL || count <= 0)
    {
        return INVALID_VALUE;
    }
    float sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += grades[i];
    }
    return sum / count;
}

int db_findById(const StudentDB* db, int id)
{
    for (int i = 0; i < db->count; i++)
    {
        if (db->students[i].id == id)
        {
            return i;
        }
    }
    return INVALID_VALUE;
}

int db_findByName(const StudentDB* db, const char* name)
{
    for (int i = 0; i < db->count; i++)
    {
        if (strstr(db->students[i].name, name))
        {
            return i;
        }
    }
    return INVALID_VALUE;
}

int db_updateName(StudentDB* db, int id, const char* newName)
{
    int index = db_findById(db, id);
    if (index == INVALID_VALUE)
    {
        return INVALID_VALUE;
    }
    strncpy_s(db->students[index].name, newName, MAX_NAME_LEN - 1);
    db->students[index].name[MAX_NAME_LEN - 1] = '\0';
    return 1;
}