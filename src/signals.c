/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbondare <mbondare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:51:53 by mbondare          #+#    #+#             */
/*   Updated: 2025/10/21 12:08:32 by mbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

volatile sig_atomic_t g_heredoc_interrupted = 0; 

//when user presses ctrl+c 
//should:print \n, display new prompt
void handle_sigin_interactivet(int sig)
{
    (void)sig;

    //global flag if interuption happens 
    g_exit_status = 130; 
    write(STDOUT_FILENO, "\n", 1);//move cursor to newline after ^C
    rl_on_new_line();//clear current input line
    rl_replace_line("", 0); //replace current line with empty line(clears internal buffer)
    rl_redisplay(); //new prompt 
}

//doc handler
//set flag to stop heredoc input loop
static void handle_sigint_heredoc(int sig)
{
    (void)sig; 
    g_heredoc_interrupted = 1; 
    g_exit_status = 130; 
    close(STDIN_FILENO); 
    write(STDOUT_FILENO, "\n", 1); 
}

//setup interactive mode 
void setup_interactive_signals(void)
{
    struct sigaction sa_int; 
    struct sigaction sa_quit; 
    //handle sigint 
    sigemptyset(&sa_int.sa_mask); 
    sa_int.sa_handler = handle_sigint_interactive; 
    sa_int.sa_flags = SA_RESTART; 
    sigaction(SIGINT, &sa_int, NULL);
    //ignore sigquit
    sigemptyset(&sa_quit.sa_mask); 
    sa_quit.sa_handler  SIG_IGN; 
    sa_quit.sa_flags = 0; 
    sigaction(SIGQUIT, &sa_quit, NULL); 
    
}

//setup child process (called after fork before execve), resets signals
void setup_child_signals(void)
{
    struct sigaction sa_default; 

    sigempty(&sa_default.sa_mask); 
    sa_default.sa_handler = SIG_DFL; 
    sa_default(SIGINT, &sa_default, NULL); 
    sigaction(SIGQUIT, &sa_default, NULL); 
}

//parent setup (ignore sigs)
void setup_parent_exec_signals(void)
{
    struct sigaction sa_ignore;
    
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_handler = SIG_IGN; 
    sa_ignore.sa_flags = 0; 
    sigaction(SIGINT, &sa_ignore, NULL); 
    sigaction(SIGQUIT, &sa_ignore, NULL); 

}

//heredoc input
void setup_heredoc_signals(void)
{
    struct sigaction sa_heredoc; 

    sigemptyset(&sa_heredoc.sa_mask); 
    sa_heredoc.sa_handler = handle_sigint_heredoc; 
    sa_heredoc.sa_flags = 0; 
    sigaction(SIGINT, &sa_heredoc, NULL); 
}



// //ignore ctrl+\ 
// //does nothing, ignore completely 
// void handle_sigquit(int sig)
// {
//     (void)sig;
//     // write(STDOUT_FILENO, "SIGQUIT ignored\n", 16);
// }

// //interactive signals for when shell is waiting for input
// //ctrl+c = display new prompt 
// //ctrl+\= ignored 
// void setup_signals(void)
// {
//     struct sigaction sa_int;
//     struct sigaction sa_quit;

// //sigint setup
//     sa_int.sa_handle = handle_sigint;
//     sigemptyset(&sa_int.sa_mask);//mask says what signals should be blocked while handle_sigint function is running 
//     sa_int.sa_flags = SA_RESTART;//restart interupted sig calls 
//     sigaction(SIGINT, &sa_int, NULL); // for sigint signal se info from sa_int

//     //sigquit setup(to ignore ctrl+\ handler)
//     sa_quit.sa_handle = SIG_IGN;//ignore signal 
//     sigemptyset(&sa_quit.sa_mask); 
//     sa_quit.sa_flags = 0; 
//     sigaction(SIGQUIT, &sa_quit, NULL); 
// }

// //called before executing command
// //ctrl+c- use default (terminate child)
// //ctrl +\- terminate child and coredump
// void execute_signals(void)
// {
//     struct sigaction sa;

//     //reset sigint to default 
//     sa.sa_handle = SIG_DFL;//signal default  
//     //apply default for SIGINT to child process 
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0; 
//     sigaction(SIGINT, &sa, NULL); 

//     //reset to default (terminate process and create core dump file )
//     sa.sa_handle = SIG_DFL; 
//     sigemptyset(&sa.sa_mask); 
//     sa.sa_flags = 0; 
//     sigaction(SIGQUIT, &sa, NULL); 
// }

// //ignore all signals for parent during execution 
// //signals delivered to child 
// void ignore_signals(void)//called by parent after fork while child running 
// {
//     struct sigaction sa; 

//     sa.sa_handle = SIG_IGN;
//     sigemptyset(&sa.sa_mask); 
//     sa.sa_flags = 0; 
//     sigaction(SIGQUIT, &sa, NULL); 
// }

// void setup_pipe_signals(void)
// {
//     struct sigaction sa; 

//     //all children set to same process group ]
//     //ctrl + c should kill whole pipeline 

//     sa.sa_handler = SIG_DFL;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0; 
//     sigaction(SIGINT, &sa, NULL);
//     sigaction(SIGQUIT, &sa, NULL); 
// }

// //not finished 
// int execute_pipes()
// {
//     pid_t pgid = 0; 
//     int i; 

//     while ()
//     {
//         pid = fork(); 
//         if (pid == 0)//if child
//         {
//             if (i == 0)
//             {
//                 setpgid(0, 0); 
//                 pgid = getpid(); 
//             }
//             else
//             {
//                 setpgid(0, pgid); //other children join group
//             }

//             setup_execution_signals(); 
//         }
//         //parent takes first child's PID
//         if (i == 0)
//             pgid = pid; 
//         else 
//             setpgid(pid, pgid); 
        
//         i++; 
//     }
// }

// //handle heredoc 