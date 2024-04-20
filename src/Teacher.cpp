#include "Teacher.h"

Teacher::Teacher()
: Person("a", "a", "a", "a", "a", 0), db("/home/yazzine/Desktop/College_Project/DB/college-project.db"){

}

Teacher::Teacher(const std::string& username, const std::string& password)
    : Person("", "", "", username, password, 0), db("/home/yazzine/Desktop/College_Project/DB/college-project.db") {
    db.get_teacher_info(username, password, &first_name, &last_name, &date_of_birth, &id);
}

void Teacher::input_mark() {
    int course_id, student_id;
    double note;

    cout << "Enter course ID: ";
    cin >> course_id;
    cout << "Enter student ID: ";
    cin >> student_id;
    cout << "Enter note: ";
    cin >> note;

    // Validate input
    if (course_id < 0 || student_id < 0 || note < 0 || note > 20) {
        cout << "Invalid input. Please enter valid course ID, student ID, and note." << endl;
        return;
    }

    db.input_mark(course_id, student_id, note);
}

void Teacher::input_attendance() {
    int course_id, student_id;

    cout << "Enter course ID: ";
    cin >> course_id;
    cout << "Enter student ID: ";
    cin >> student_id;

    // Validate input
    if (course_id < 0 || student_id < 0) {
        cout << "Invalid input. Please enter valid course ID and student ID." << endl;
        return;
    }

    db.input_attendance(course_id, student_id);
}


