#include <iostream>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include <cstdlib>
#include <sys/wait.h>

int main (int argc, char **argv)
{
    int rgenToPy[2];
    int pyToC[2];
    pipe(rgenToPy);
    pipe(pyToC);
    std::vector<pid_t> children;
    pid_t child=fork();
    if(child==0)
    {
        if(dup2(rgenToPy[1], STDOUT_FILENO)!=1)
        {
            std::cerr<<"Error opening for rgen"<<std::endl;
        }
        close(rgenToPy[0]);
        close(rgenToPy[1]);
        close(pyToC[0]);
        close(pyToC[1]);
        std::cerr<<execvp("./rgen",argv)<< "from execvp rgen"<<std::endl;
        std::cerr << "Error: in execvp rgen\n";
        abort ();
    }
    else if (child < 0)
    {
        std::cerr << "Error: could not fork for first time.\n";
    }

    children.push_back(child);
    child=fork();
    if(child==0)
    {
        if(dup2(rgenToPy[0], STDIN_FILENO)!=0 || dup2(pyToC[1],STDOUT_FILENO)!=1)
        {
            std::cerr<<"Error: opening for python"<<std::endl;
        }
        close(rgenToPy[1]);
        close(rgenToPy[0]);
        close(pyToC[0]);
        close(pyToC[1]);
        execl("/usr/bin/python", "/usr/bin/python", "./a1-ece650.py", (char *)NULL);
        std::cerr << "Error: in execvp python \n";
        abort ();
    }
    else if (child < 0)
    {
        std::cerr << "Error: could not fork for second time.\n";
    }
    children.push_back(child);

    child=fork();
    if(child==0)
    {
        if(dup2(pyToC[0], STDIN_FILENO)!=0)
        {
           std::cerr<<"Error: opening for assignment2"<<std::endl;
        }
        close(pyToC[1]);
        close(pyToC[0]);
        close(rgenToPy[1]);
        close(rgenToPy[0]);
        execvp("./a2-ece650",argv);
    }
    else if (child < 0)
    {
        std::cerr << "Error: could not fork for third time.\n";
    }
    children.push_back(child);

        if(dup2(pyToC[1],STDOUT_FILENO)!=1)
        {
            std::cerr<<"Error: opening for console"<<std::endl;
        }
        close(rgenToPy[1]);
        close(rgenToPy[0]);
        close(pyToC[0]);
        close(pyToC[1]);
        while (!std::cin.eof())
        {
            std::string line;
            std::getline(std::cin, line);
            if (line == ""){
					break;
            }
            std::cout<<line<<std::endl;
        }
    
    for (pid_t kids : children)
    {
        int status;
        kill (kids, SIGKILL);
        waitpid(kids, &status, 0);
    }
    return 0;
}