
# Student Management System in C

A simple and efficient Student Management System built using C with role-based access control and file handling.

## Features

### Role-Based Login
- Admin: Add, Display, Search, Update, Delete Students  
- Staff: Add, Display, Search, Update  
- Guest: Display, Search  

### Student Operations
- Add new student  
- Display all students  
- Search student  
- Update student  
- Delete student  

### File Handling
The system stores data in:
- students.txt — Student records  
- credentials.txt — Login details  

## Project Structure
```
student-management-system/
│
├── main.c
├── credentials.txt
├── students.txt
├── README.md
└── sample_output.txt
```

## Sample Credentials
```
admin 1234 admin
staff 2222 staff
guest 0000 guest
```

## Sample Student Records
```
101 Rahul 87.50
102 Sneha 92.00
103 Kiran 76.30
```

## How to Compile
```
gcc main.c -o sms
```

## How to Run
```
./sms
```

## Future Improvements
- Password masking  
- Sorting options  
- Binary file storage  
- GUI version  
