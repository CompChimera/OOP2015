/*
 * OS32 Setup Program
 *
 * Written by Brittany Kelly & Izik Arruda
 * Testing done by Bana (Mac Arcitecture)
 * Creates the folder structures of OS32
 * Runs before the main executable of the Operating System
 *
 */
//Interaction with the user (may or may not be used)
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>  /* defines FILENAME_MAX */
#include <sys/stat.h>
#if defined(WINDOWS)
    #include <windows.h>
   #define GetCurrentDir _getcwd
#elif defined(__APPLE__)
    #include <unistd.h>
    #define GetCurrentDir getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif

//Creates the directories needed by the rest of the system
void createDirectories(char curOS) {
    //Use different sections depending on the OS typef
    //w for windows
    //m for apple (mac)
    if(curOS == 'w') {
        //Variables
        //char buffer to hold the directory path name
        char cCurrentPath[FILENAME_MAX];
        //System path name
        char cSystemPath[FILENAME_MAX];
        //Account path name
        char cAccountPath[FILENAME_MAX];
        //Did the function work
        if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
        {
            //return 1;
            return;
        }

        strcat (cCurrentPath, "/OS32");
        //Initalize the other paths as needed by appending the folder names to the current directory
        strcat (cSystemPath, cCurrentPath);     strcat (cSystemPath, "/systems");
        strcat (cAccountPath, cSystemPath);     strcat (cAccountPath, "/account");

        //TEST: print out the current directory (Of the running executable - might not the where the code is
        printf ("The current working directory is %s\n", cCurrentPath);

        //Create new directory
        mkdir (cCurrentPath, ACCESSPERMS);
        printf ("The directory was made: %s\n", cCurrentPath);
        mkdir (cSystemPath, ACCESSPERMS);
        printf ("The directory was made: %s\n", cSystemPath);
        mkdir (cAccountPath, ACCESSPERMS);
        printf ("The directory was made: %s\n", cAccountPath);
    }
    else if( curOS == 'm' ){
        mkdir("OS32", 0777);
        mkdir("OS32/systems", 0777);
        mkdir("OS32/systems/account", 0777);
    }
    else {
        mkdir("OS32", 0777);
        mkdir("OS32/systems", 0777);
        mkdir("OS32/systems/account", 0777);
    }
}

//Creates the startup files
//Written by Izik Arruda
void createFilesW() {

    //create a stream to output the files' contents
    std::ofstream fileCreation;

    //configuration file holding memory data
    fileCreation.open("OS32\\systems\\OS32.config");
    fileCreation << "" << std::endl;
    fileCreation.close();

    //file to hold the list of file properties
    fileCreation.open("OS32\\systems\\file-property.log");
    fileCreation << "" << std::endl;
    fileCreation.close();

    //list of commands the user can use
    fileCreation.open("OS32\\systems\\command-list.txt");
    fileCreation <<
    "helpme\n"
            "fcreate\n"
            "fread\n"
            "fwrite\n"
            "dcreate\n"
            "currdir\n"
            "listitems\n"
            "chper" << std::endl;
    fileCreation.close();

    //description of all commands, possibly run when helpme is called
    fileCreation.open("OS32\\systems\\command-help.txt");
    fileCreation <<
    "helpme \t\t\t\t: To display the set of commands that are available\n"
            "fcreate <file name> \t\t: To create a file\n"
            "fread <file name> \t\t: To read from a file that has read permission, or else display error\n"
            "fwrite <file name> <contents> \t\t: To write to a file that has read-write permission or else display error with the given content\n"
            "dcreate <directory name> \t: To create a new directory\n"
            "currdir \t\t\t: To display the name of the current directory\n"
            "listitems \t\t\t: To display the names of all the files and directories within the current directory\n"
            "chper <file name> <permission> \t: This changes the permission type for the file" << std::endl;
    fileCreation.close();

    //all user accounts information
    fileCreation.open("OS32\\systems\\account\\user-accounts.txt");
    fileCreation << "admin\npassword\n";
    fileCreation << "" << std::endl;
    fileCreation.close();

    //current logged in user information
    fileCreation.open("OS32\\systems\\account\\current-login.txt");
    fileCreation << "" << std::endl;
    fileCreation.close();

    //logged login timestamps
    fileCreation.open("OS32\\systems\\account\\login-history.txt");
    fileCreation << "" << std::endl;
    fileCreation.close();
}
//Creates the startup files
//Written by Izik Arruda
void createFilesM() {

    //create a stream to output the files' contents
    std::ofstream fileCreation;

    //configuration file holding memory data
    fileCreation.open("OS32/systems/OS32.config");
    fileCreation << "" << std::endl;
    fileCreation.close();

    //file to hold the list of file properties
    fileCreation.open("OS32/systems/file-property.log");
    fileCreation << "" << std::endl;
    fileCreation.close();

    //list of commands the user can use
    fileCreation.open("OS32/systems/command-list.txt");
    fileCreation <<
    "helpme\n"
            "fcreate\n"
            "fread\n"
            "fwrite\n"
            "dcreate\n"
            "currdir\n"
            "listitems\n"
            "chper" << std::endl;
    fileCreation.close();

    //description of all commands, possibly run when helpme is called
    fileCreation.open("OS32/systems/command-help.txt");
    fileCreation <<
    "helpme \t\t\t\t: To display the set of commands that are available\n"
            "fcreate <file name> \t\t: To create a file\n"
            "fread <file name> \t\t: To read from a file that has read permission, or else display error\n"
            "fwrite <file name> <contents> \t\t: To write to a file that has read-write permission or else display error with the given content\n"
            "dcreate <directory name> \t: To create a new directory\n"
            "currdir \t\t\t: To display the name of the current directory\n"
            "listitems \t\t\t: To display the names of all the files and directories within the current directory\n"
            "chper <file name> <permission> \t: This changes the permission type for the file" << std::endl;
    fileCreation.close();

    //all user accounts information
    fileCreation.open("OS32/systems/account/user-accounts.txt");
    fileCreation << "admin\npassword\n";
    fileCreation << "" << std::endl;
    fileCreation.close();

    //current logged in user information
    fileCreation.open("OS32/systems/account/current-login.txt");
    fileCreation << "" << std::endl;
    fileCreation.close();

    //logged login timestamps
    fileCreation.open("OS32/systems/account/login-history.txt");
    fileCreation << "" << std::endl;
    fileCreation.close();
}
int main() {
    //Creates the directories for OS32
    //Takes in a parameter depending on the operating system

    //Creates necessary files
    //Calls a different function depending on the operating system
#if defined(WINDOWS)
        createDirectories('w');
        createFilesW();
    #elif defined(__APPLE__)
        createDirectories('m');
        createFilesM();
#endif

    printf("Ready to run OS32");
    return 0;
}