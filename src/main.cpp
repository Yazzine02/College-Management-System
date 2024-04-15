#include <iostream>
#include "Database.h"

using namespace std;

int main(){
	Database db("/home/yazzine/Desktop/College_Project/DB/college-project.db");
	db.add_teacher("tes","tes?","bi","ba","01/02/2002");
	db.remove_teacher(1);
	return 0;
}
