#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

namespace hogason {

	int orphan()
	{
		pid_t pid;
		//����һ������
		pid = fork();
		//����ʧ��
		if (pid < 0)
		{
			perror("fork error:");
			exit(1);
		}
		//�ӽ���
		if (pid == 0)
		{
			printf("I am the child process.\n");
			//�������ID�͸�����ID
			printf("pid: %d\tppid:%d\n", getpid(), getppid());
			printf("I will sleep five seconds.\n");
			//˯��5s����֤���������˳�
			sleep(5);
			printf("pid: %d\tppid:%d\n", getpid(), getppid());
			printf("child process is exited.\n");
		}
		//������
		else
		{
			printf("I am father process.\n");
			//������˯��1s����֤�ӽ����������id
			sleep(1);
			printf("father process is  exited.\n");
		}
		return 0;
	}

	int zombie()
	{
		pid_t pid;
		pid = fork();
		if (pid < 0)
		{
			perror("fork error:");
			exit(1);
		}
		else if (pid == 0)
		{
			printf("I am child process.I am exiting.\n");
			exit(0);
		}
		printf("I am father process.I will sleep two seconds\n");
		//�ȴ��ӽ������˳�
		sleep(2);
		//���������Ϣ
		system("ps -o pid,ppid,state,tty,command");
		printf("father process is exiting.\n");
		return 0;
	}

	int zombieloop()
	{
		pid_t  pid;
		//ѭ�������ӽ���
		while (1)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork error:");
				exit(1);
			}
			else if (pid == 0)
			{
				printf("I am a child process.\nI am exiting.\n");
				//�ӽ����˳�����Ϊ��ʬ����
				exit(0);
			}
			else
			{
				//����������20s���������ӽ���
				sleep(20);
				continue;
			}
		}
		return 0;
	}

	static void sig_child(int signo)
	{
		pid_t pid;
		int stat;

		//����ʬ����
		while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		{
			printf("child %d terminated.\n", pid);
		}
	}

	int handle_sig()
	{
		pid_t pid;
		//������׽�ӽ����˳��ź�
		signal(SIGCHLD, sig_child);
		pid = fork();
		if (pid < 0)
		{
			perror("fork error:");
			exit(1);
		}
		else if (pid == 0)
		{
			printf("I am child process,pid id %d.I am exiting.\n", getpid());
			exit(0);
		}
		printf("I am father process.I will sleep two seconds\n");
		//�ȴ��ӽ������˳�
		sleep(2);
		//���������Ϣ
		system("ps -o pid,ppid,state,tty,command");
		printf("father process is exiting.\n");
		return 0;
	}

	int fork_double()
	{
		pid_t  pid;
		//������һ���ӽ���
		pid = fork();
		if (pid < 0)
		{
			perror("fork error:");
			exit(1);
		}
		//��һ���ӽ���
		else if (pid == 0)
		{
			//�ӽ����ٴ����ӽ���
			printf("I am the first child process.pid:%d\tppid:%d\n", getpid(), getppid());
			pid = fork();
			if (pid < 0)
			{
				perror("fork error:");
				exit(1);
			}
			//��һ���ӽ����˳�
			else if (pid >0)
			{
				printf("first procee is exited.\n");
				exit(0);
			}
			//�ڶ����ӽ���
			//˯��3s��֤��һ���ӽ����˳��������ڶ����ӽ��̵ĸ��׾���init������
			sleep(3);
			printf("I am the second child process.pid: %d\tppid:%d\n", getpid(), getppid());
			exit(0);
		}
		//�����̴����һ���ӽ����˳�
		if (waitpid(pid, NULL, 0) != pid)
		{
			perror("waitepid error:");
			exit(1);
		}
		exit(0);
		return 0;
	}
}