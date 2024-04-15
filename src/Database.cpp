#include "Database.h"
 
Database::Database(const string& dbPath){
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Database connection established successfully." << endl;
    }
}
Database::~Database() {
    if (sqlite3_close(db) != SQLITE_OK) {
        cerr << "Error closing database: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Database connection closed." << endl;
    }
}

//------------------------------------------------------------------------------------------------------
 // STUDENT SECTION
bool Database::create_student(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth) {
    // Check if the username already exists
    std::string query = "SELECT COUNT(*) FROM Student WHERE username = ?";
    sqlite3_stmt* statement;
    int result;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            result = sqlite3_column_int(statement, 0);
        }
	
        sqlite3_finalize(statement);
    }

    // If username already exists, return false
    if (result > 0) {
    	cout<<"Username or password exists already."<<endl;
        return false;
    }

    // Insert the new student
    query = "INSERT INTO Student (username, password) VALUES (?, ?)";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_DONE) {
            sqlite3_finalize(statement);
            cout<<"Student created successfully"<<endl;
            return true; // Student created successfully
        }
    }

    // Error occurred during insertion
    return false;
};

bool Database::login_student(const std::string& username, const std::string& password) {
    // Check if the username and password match
    std::string query = "SELECT COUNT(*) FROM Student WHERE username = ? AND password = ?";
    sqlite3_stmt* statement;
    int result;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            result = sqlite3_column_int(statement, 0);
        }

        sqlite3_finalize(statement);
    }

    // If username and password match, return true
    return (result > 0);
};

unordered_map<int,double> Database::get_grades(int student_id){
	string query = "SELECT course_id,mark FROM Mark WHERE student_id=?";
	sqlite3_stmt* statement;
	unordered_map<int,double> grades;
	
	// Prepare the SQL statement
	    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
		// Bind the student_id parameter
		sqlite3_bind_int(statement, 1, student_id);

		// Execute the query
		while (sqlite3_step(statement) == SQLITE_ROW) {
		    // Fetch the course_id and mark from the result
		    int course_id = sqlite3_column_int(statement, 0);
		    double mark = sqlite3_column_double(statement, 1);
		    // Store the course_id and mark in the unordered_map
		    grades.insert({course_id, mark});
		}

		// Finalize the statement
		sqlite3_finalize(statement);
	    } else {
		cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
	    }

	    return grades;
};

vector<int> Database::check_attendance(int student_id){
	string query = "SELECT course_id FROM Attendance WHERE student_id=?";
	sqlite3_stmt* statement;
	vector<int> attendances;
	
	if(sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK){
		// Bind the student_id parameter
		sqlite3_bind_int(statement, 1, student_id);
		while (sqlite3_step(statement) == SQLITE_ROW) {
		    // Fetch the course_id and mark from the result
		    int course_id = sqlite3_column_int(statement, 0);
		    // Store the course_id in the vector
		    attendances.push_back(course_id);
		}

		// Finalize the statement
		sqlite3_finalize(statement);
	} else {
		cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
	}
	return attendances;
};

//----------------------------------------------------------------------------------------------
// TEACHER SECTION
bool Database::create_teacher(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth) {
    // Check if the username already exists
    std::string query = "SELECT COUNT(*) FROM Teacher WHERE username = ?";
    sqlite3_stmt* statement;
    int result;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            result = sqlite3_column_int(statement, 0);
        }

        sqlite3_finalize(statement);
    }

    // If username already exists, return false
    if (result > 0) {
    	cout<<"Username or password exists already."<<endl;
        return false;
    }

    // Insert the new teacher
    query = "INSERT INTO Teacher (username, password) VALUES (?, ?)";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_DONE) {
            sqlite3_finalize(statement);
            cout<<"Teacher created successfully"<<endl;
            return true; // Teacher created successfully
        }
    }

    // Error occurred during insertion
    return false;
};

bool Database::login_teacher(const std::string& username, const std::string& password) {
    // Check if the username and password match
    std::string query = "SELECT COUNT(*) FROM Teacher WHERE username = ? AND password = ?";
    sqlite3_stmt* statement;
    int result;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            result = sqlite3_column_int(statement, 0);
        }

        sqlite3_finalize(statement);
    }

    // If username and password match, return true
    return (result > 0);
};


//--------------------------------------------------------------------------------------------------
// HEAD OF DEPARTEMENT SECTION
bool Database::create_headofdepartement(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth) {
    // Check if the username already exists
    std::string query = "SELECT COUNT(*) FROM HeadOfDepartement WHERE username = ?";
    sqlite3_stmt* statement;
    int result;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            result = sqlite3_column_int(statement, 0);
        }

        sqlite3_finalize(statement);
    }

    // If username already exists, return false
    if (result > 0) {
    	cout<<"Username or password exists already."<<endl;
        return false;
    }

    // Insert the new head of departement
    query = "INSERT INTO HeadOfDepartement (username, password) VALUES (?, ?)";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_DONE) {
            sqlite3_finalize(statement);
            cout<<"Head of departement created successfully"<<endl;
            return true; // Student created successfully
        }
    }

    // Error occurred during insertion
    return false;
};

bool Database::login_headofdepartement(const std::string& username, const std::string& password) {
    // Check if the username and password match
    std::string query = "SELECT COUNT(*) FROM HeadOfDepartement WHERE username = ? AND password = ?";
    sqlite3_stmt* statement;
    int result;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            result = sqlite3_column_int(statement, 0);
        }

        sqlite3_finalize(statement);
    }

    // If username and password match, return true
    return (result > 0);
};

bool Database::input_mark(int course_id, int student_id, double note) {
    string query = "INSERT INTO Mark (course_id, student_id, mark) VALUES (?, ?, ?)";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_int(statement, 1, course_id);
        sqlite3_bind_int(statement, 2, student_id);
        sqlite3_bind_double(statement, 3, note);

        if (sqlite3_step(statement) == SQLITE_DONE) {
            sqlite3_finalize(statement);
            cout << "Mark input successfully" << endl;
            return true; // Mark input successfully
        } else {
            cerr << "Error inputting mark: " << sqlite3_errmsg(db) << endl;
        }
    } else {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    }
    
    return false; // Return false if the operation fails
};

bool Database::input_attendance(int course_id,int student_id){
    string query = "INSERT INTO Attendance (course_id, student_id) VALUES (?, ?)";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_int(statement, 1, course_id);
        sqlite3_bind_int(statement, 2, student_id);

        if (sqlite3_step(statement) == SQLITE_DONE) {
            sqlite3_finalize(statement);
            cout << "Attendance input successfully" << endl;
            return true; // Attendance input successfully
        } else {
            cerr << "Error inputting attendance: " << sqlite3_errmsg(db) << endl;
        }
    } else {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    }
    
    return false; // Return false if the operation fails
};


bool Database::add_teacher(const std::string& username, const std::string& password,  const std::string& first_name, const std::string& last_name, const std::string& date_of_birth){
	return create_teacher(username,password,first_name,last_name,date_of_birth);
};

bool Database::remove_teacher(int teacher_id){
	string query = "DELETE FROM Teacher WHERE teacher_id=?";
	sqlite3_stmt* statement;
	
	if(sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK){
		sqlite3_bind_int(statement, 1, teacher_id);
		if (sqlite3_step(statement) == SQLITE_DONE) {
            		sqlite3_finalize(statement);
            		cout << "Teacher removed successfully" << endl;
           		 return true; // Teacher removed successfully
        	} else {
            		cerr << "Error removing teacher: " << sqlite3_errmsg(db) << endl;
        	}
    		} else {
        		cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    		}
    
    		return false; // Return false if the operation fails
};

bool Database::add_student(const std::string& username, const std::string& password, const std::string& first_name, const std::string& last_name, const std::string& date_of_birth){
	return create_student(username,password,first_name,last_name,date_of_birth)
};

bool Database::remove_student(int student_id){
	string query = "DELETE FROM Student WHERE student_id=?";
	sqlite3_stmt* statement;
	
	if(sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK){
		sqlite3_bind_int(statement, 1, student_id);
		if (sqlite3_step(statement) == SQLITE_DONE) {
            		sqlite3_finalize(statement);
            		cout << "Student removed successfully" << endl;
           		 return true; // Student removed successfully
        	} else {
            		cerr << "Error removing student: " << sqlite3_errmsg(db) << endl;
        	}
    		} else {
        		cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    		}
    
    		return false; // Return false if the operation fails
};

bool Database::add_course(const string& title,const string& description){
	string query = "INSERT INTO Course (title,description) VALUES (?,?)";
	sqlite3_stmt* statement;
	
	if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        	sqlite3_bind_text(statement, 1, title.c_str(), -1, SQLITE_STATIC);
        	sqlite3_bind_text(statement, 2, description.c_str(), -1, SQLITE_STATIC);

        	if (sqlite3_step(statement) == SQLITE_DONE) {
            		sqlite3_finalize(statement);
            		cout << "Course input successfully" << endl;
            		return true; // Course input successfully
        	} else {
            		cerr << "Error inputting course: " << sqlite3_errmsg(db) << endl;
        	}
    	} else {
        	cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    	}
    	return false; // Return false if the operation fails
};

bool Database::remove_course(int course_id){
	string query = "DELETE FROM Course WHERE course_id=?";
	sqlite3_stmt* statement;
	
	if(sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK){
		sqlite3_bind_int(statement, 1, course_id);
		if (sqlite3_step(statement) == SQLITE_DONE) {
            		sqlite3_finalize(statement);
            		cout << "Course removed successfully" << endl;
           		 return true; // Course removed successfully
        	} else {
            		cerr << "Error removing course: " << sqlite3_errmsg(db) << endl;
        	}
    		} else {
        		cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    		}
    
    		return false; // Return false if the operation fails
};
