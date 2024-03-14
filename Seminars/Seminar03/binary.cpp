#include <iostream>
#include <fstream>

#pragma warning (disable : 4996)

struct Subject {
    char* name;
    int credits;
};

struct Teacher {
    Subject subjects[10];
    int subjectsCount;
    double salary;
};

struct Team {
    Teacher* teachers;
    int teachersCount;
    Subject subject;
};

void writeSubjectToFile(std::ofstream& outFile, const Subject& subject) {
    size_t nameLen = strlen(subject.name);

    outFile.write((const char*)&nameLen, sizeof(nameLen));
    outFile.write(subject.name, nameLen);

    outFile.write((const char*)&subject.credits, sizeof(subject.credits));
}

Subject readSubjectFromFile(std::ifstream& inFile) {
    Subject res;

    size_t nameLen;

    inFile.read((char*)&nameLen, sizeof(nameLen));

    res.name = new char[nameLen + 1];
    inFile.read(res.name, nameLen);
    res.name[nameLen] = '\0';

    inFile.read((char*)&res.credits, sizeof(res.credits));

    return res;
}

void writeTeacherToFile(std::ofstream& outFile, const Teacher& teacher) {
    outFile.write((const char*)&teacher.subjectsCount, sizeof(teacher.subjectsCount));
    for (size_t i = 0; i < teacher.subjectsCount; i++) {
        writeSubjectToFile(outFile, teacher.subjects[i]);
    }

    outFile.write((const char*)&teacher.salary, sizeof(teacher.salary));
}

Teacher readTeacherFromFile(std::ifstream& inFile) {
    Teacher teacher;
    inFile.read((char*)&teacher.subjectsCount, sizeof(teacher.subjectsCount));
    for (size_t i = 0; i < teacher.subjectsCount; i++) {
        teacher.subjects[i] = readSubjectFromFile(inFile);
    }

    inFile.read((char*)&teacher.salary, sizeof(teacher.salary));
    return teacher;
}

void writeTeamToFile(std::ofstream& outFile, const Team& team) {
    outFile.write((const char*)&team.teachersCount, sizeof(team.teachersCount));

    for (size_t i = 0; i < team.teachersCount; i++) {
        writeTeacherToFile(outFile, team.teachers[i]);
    }

    writeSubjectToFile(outFile, team.subject);
}

Team readTeamFromFile(std::ifstream& inFile) {
    Team team;

    inFile.read((char*)&team.teachersCount, sizeof(team.teachersCount));
    team.teachers = new Teacher[team.teachersCount];
    
    for (size_t i = 0; i < team.teachersCount; i++) {
        team.teachers[i] = readTeacherFromFile(inFile);
    }

    team.subject = readSubjectFromFile(inFile);

    return team;
}

Team generateTeam() {
    Team team;

    team.teachersCount = 3;
    team.teachers = new Teacher[team.teachersCount];

    for (int i = 0; i < team.teachersCount; ++i) {
        team.teachers[i].subjectsCount = 1; 
        team.teachers[i].salary = 50000.0; 
        team.teachers[i].subjects[0].name = new char[20];
        strcpy(team.teachers[i].subjects[0].name, "Mathematics");
        team.teachers[i].subjects[0].credits = 4;
    }

    team.subject.name = new char[20]; 
    strcpy(team.subject.name, "Mathematics"); 
    team.subject.credits = 4; 

    return team;
}

void freeTeam(Team& team) {
    for (int i = 0; i < team.teachersCount; ++i) {
        for (int j = 0; j < team.teachers[i].subjectsCount; ++j) {
            delete[] team.teachers[i].subjects[j].name;
        }
    }
    delete[] team.subject.name;
    delete[] team.teachers;
}

int main()
{
    Team team = generateTeam();
    std::ofstream outFile("teachers.dat", std::ios::binary);

    writeTeamToFile(outFile, team);
    outFile.close();

    std::ifstream inFile ("teachers.dat", std::ios::binary);
    team = readTeamFromFile(inFile);

    std::cout << "Generated Team:\n";
    std::cout << "Number of teachers: " << team.teachersCount << std::endl;
    std::cout << "Subject: " << team.subject.name << std::endl;
    std::cout << "Subject credits: " << team.subject.credits << std::endl;

    freeTeam(team);
}
