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
// UTILITIES
void Database::get_student_info(const std::string& username, const std::string& password, std::string* first_name, std::string* last_name, std::string* date_of_birth, int* student_id) {
    // Prepare the query to retrieve student information
    std::string query = "SELECT first_name, last_name, date_of_birth, student_id FROM Student WHERE username = ? AND password = ?";
    sqlite3_stmt* statement;
    // Prepare the statement
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        // Bind parameters (username and password)
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

        // Execute the query
        if (sqlite3_step(statement) == SQLITE_ROW) {
            // Retrieve values from the result
            const unsigned char* fetchedFirstName = sqlite3_column_text(statement, 0);
            const unsigned char* fetchedLastName = sqlite3_column_text(statement, 1);
            const unsigned char* fetchedDateOfBirth = sqlite3_column_text(statement, 2);
            int fetchedStudentID = sqlite3_column_int(statement, 3);
            	/*
            	  +columns 0, 1, and 2, which correspond to the first name, last name, and date of birth columns, respectively.
            	  +fetching the student ID from column 3.
            	  +const unsigned char*: This is the data type returned by sqlite3_column_text. It represents a pointer to an array of characters (i.e., a string) in memory.
            	  +reinterpret_cast<const char*>(fetchedFirstName): This is a type cast that converts the pointer to the first name string from const unsigned char* to const char*. It's necessary because we want to create a std::string from it, and std::string expects a const char*.
            	*/

            // Store the retrieved values in the variables pointed to by the pointers
            *first_name = std::string(reinterpret_cast<const char*>(fetchedFirstName));
            *last_name = std::string(reinterpret_cast<const char*>(fetchedLastName));
            *date_of_birth = std::string(reinterpret_cast<const char*>(fetchedDateOfBirth));
            *student_id = fetchedStudentID;
            /**/
        } else {
            // Handle the case where username/password not found
            cout<<"Username or password doesn't exist."<<endl;
        }

        // Finalize the statement
        sqlite3_finalize(statement);
    } else {
        // Handle the case where statement preparation fails
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    }
}

void Database::get_teacher_info(const string& username, const string& password, string* first_name, string* last_name, string* date_of_birth, int* teacher_id) {
    string query = "SELECT first_name, last_name, date_of_birth, teacher_id FROM Teacher WHERE username = ? AND password = ?";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            *first_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
            *last_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
            *date_of_birth = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
            *teacher_id = sqlite3_column_int(statement, 3);
        } else {
            cerr << "Username or password doesn't exist." << endl;
        }

        sqlite3_finalize(statement);
    } else {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    }
}

void Database::get_head_of_departement_info(const string& username, const string& password, string* first_name, string* last_name, string* date_of_birth, int* hod_id) {
    string query = "SELECT first_name, last_name, date_of_birth, hod_id FROM HeadOfDepartement WHERE username = ? AND password = ?";
    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            *first_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
            *last_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
            *date_of_birth = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
            *hod_id = sqlite3_column_int(statement, 3);
        } else {
            cerr << "Username or password doesn't exist." << endl;
        }

        sqlite3_finalize(statement);
    } else {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
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
    query = "INSERT INTO Student (username, password,first_name,last_name,date_of_birth) VALUES (?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 3, first_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 4, last_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 5, date_of_birth.c_str(), -1, SQLITE_STATIC);

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

    bool login_successful = (result == 1);
    if (login_successful) {
        cout << "Student logged in successfully" << endl;
    } else {
        cout << "Student login failed. Please check your username or password." << endl;
    }
    
    return login_successful;
};

unordered_map<int,double> Database::get_grades(int student_id){
	if (student_id < 0) {
		cout << "Invalid input. Please enter valid student ID." << endl;
		return unordered_map<int,double>();
    	}
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

vector<int> Database::get_attendance(int student_id){
	if (student_id < 0) {
		cout << "Invalid input. Please enter valid student ID." << endl;
		return vector<int>();
    	}
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
    query = "INSERT INTO Teacher (username, password,first_name,last_name,date_of_birth) VALUES (?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 3, first_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 4, last_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 5, date_of_birth.c_str(), -1, SQLITE_STATIC);

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

    bool login_successful = (result == 1);
    if (login_successful) {
        cout << "Teacher logged in successfully" << endl;
    } else {
        cout << "Teacher login failed. Please check your username or password." << endl;
    }
    
    return login_successful;
};

bool Database::input_mark(int course_id, int student_id, double note) {
    if (course_id < 0 || student_id < 0 || note < 0 || note > 20) {
        cout << "Invalid input. Please enter valid course ID, student ID, and note." << endl;
        return false;
    }
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
    if (course_id < 0 || student_id < 0) {
        cout << "Invalid input. Please enter valid course ID and student ID." << endl;
        return false;
    }
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
    	cout<<"Username exists already."<<endl;
        return false;
    }

    // Insert the new head of departement
    query = "INSERT INTO HeadOfDepartement (username, password,first_name,last_name,date_of_birth) VALUES (?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_text(statement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 3, first_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 4, last_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 5, date_of_birth.c_str(), -1, SQLITE_STATIC);

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

    bool login_successful = (result == 1);
    if (login_successful) {
        cout << "Head of departement logged in successfully" << endl;
    } else {
        cout << "Head of departement login failed. Please check your username or password." << endl;
    }
    
    return login_successful;
};

bool Database::add_teacher(const std::string& username, const std::string& password,  const std::string& first_name, const std::string& last_name, const std::string& date_of_birth){
	return create_teacher(username,password,first_name,last_name,date_of_birth);
};

bool Database::remove_teacher(int teacher_id){
	if (teacher_id < 0) {
		cout << "Invalid input. Please enter valid teache ID." << endl;
		return false;
    	}
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
	return create_student(username,password,first_name,last_name,date_of_birth);
};

bool Database::remove_student(int student_id){
	if (student_id < 0) {
        	cout << "Invalid input. Please enter valid student ID." << endl;
       		return false;
    	}
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
	if (course_id < 0) {
		cout << "Invalid input. Please enter valid course ID." << endl;
		return false;
    	}
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

bool Database::search_student(int student_id) {
    string query = "SELECT student_id, username, password, first_name, last_name, date_of_birth FROM Student WHERE student_id=?";
    sqlite3_stmt* statement;
    int result = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_int(statement, 1, student_id); // Bind the integer student_id

        if (sqlite3_step(statement) == SQLITE_ROW) {
			result = 1;
			// Fetch id, username, password, first_name, last_name, and date_of_birth
			int id = sqlite3_column_int(statement, 0);
			string username = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			string password = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
			string first_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
			string last_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 4));
			string date_of_birth = reinterpret_cast<const char*>(sqlite3_column_text(statement, 5));
			// Output or use the retrieved data
			cout << "User found. Student ID: " << id << ", Username: " << username << ", Password: " << password
				 << ", First Name: " << first_name << ", Last Name: " << last_name
				 << ", Date of Birth: " << date_of_birth << endl;
			} else {
            cout << "Student not found. Please check the student id." << endl;
        }

        sqlite3_finalize(statement);
    } else {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    }

    return result == 1;
}

bool Database::search_teacher(int teacher_id) {
    string query = "SELECT teacher_id, username, password, first_name, last_name, date_of_birth FROM Teacher WHERE teacher_id=?";
    sqlite3_stmt* statement;
    int result = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_int(statement, 1, teacher_id); // Bind the integer teacher_id

        if (sqlite3_step(statement) == SQLITE_ROW) {
			result = 1;
			// Fetch id, username, password, first_name, last_name, and date_of_birth
			int id = sqlite3_column_int(statement, 0);
			string username = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			string password = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
			string first_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
			string last_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 4));
			string date_of_birth = reinterpret_cast<const char*>(sqlite3_column_text(statement, 5));
			// Output or use the retrieved data
			cout << "User found. Teacher ID: " << id << ", Username: " << username << ", Password: " << password
				 << ", First Name: " << first_name << ", Last Name: " << last_name
				 << ", Date of Birth: " << date_of_birth << endl;
		} else {
            cout << "Teacher not found. Please check the teacher id." << endl;
        }

        sqlite3_finalize(statement);
    } else {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    }

    return result == 1;
}

bool Database::search_headofdepartement(int hod_id) {
    string query = "SELECT hod_id, username, password, first_name, last_name, date_of_birth FROM HeadOfDepartement WHERE hod_id=?";
    sqlite3_stmt* statement;
    int result = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        sqlite3_bind_int(statement, 1, hod_id); // Bind the integer hod_id

        if (sqlite3_step(statement) == SQLITE_ROW) {
			result = 1;
			// Fetch id, username, password, first_name, last_name, and date_of_birth
			int id = sqlite3_column_int(statement, 0);
			string username = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
			string password = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
			string first_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
			string last_name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 4));
			string date_of_birth = reinterpret_cast<const char*>(sqlite3_column_text(statement, 5));
			// Output or use the retrieved data
			cout << "User found. Head of Departement ID: " << id << ", Username: " << username << ", Password: " << password
				 << ", First Name: " << first_name << ", Last Name: " << last_name
				 << ", Date of Birth: " << date_of_birth << endl;
		} else {
            cout << "Head of departement not found. Please check the head of departement id." << endl;
        }

        sqlite3_finalize(statement);
    } else {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    }

    return result == 1;
}
