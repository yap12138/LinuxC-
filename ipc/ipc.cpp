#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>    // O_WRONLY
#include <sys/stat.h>
#include <ctime>
#include <errno.h>

namespace hogason {
	int ipc_pipe()
	{
		int fd[2]; //�ļ�������
		pid_t pid;
		char buff[20];

		if (pipe(fd) < 0) // �����ܵ�
		{
			printf("Create Pipe Error!\n");
			return -1;
		}

		if ((pid = fork()) < 0) // �����ӽ���
		{
			printf("Fork Error!\n");
			return -2;
		}
		else if (pid > 0) // ������
		{
			close(fd[0]); // �رն���
			write(fd[1], "hello my child!\n", 17);
			printf("parent process: sent ok.\n");
		}
		else
		{
			close(fd[1]);
			read(fd[0], buff, 20);
			printf("child process: %s", buff);
			//system("ps -o pid,ppid,state,tty,command");
		}
		return 0;
	}

	int ipc_write_fifo() 
	{
		int fd;
		int n, i;
		char buf[1024];
		time_t tp;

		printf("I am %d process.\n", getpid()); // ˵������ID

		if ((fd = open("fifo1", O_WRONLY)) < 0) // ��д��һ��FIFO 
		{
			perror("Open FIFO Failed");
			exit(1);
		}

		for (i = 0; i < 10; ++i)
		{
			time(&tp);  // ȡϵͳ��ǰʱ��
			n = sprintf(buf, "Process %d's time is %s", getpid(), ctime(&tp));
			printf("Send message: %s", buf); // ��ӡ
			if (write(fd, buf, n + 1) < 0)  // д�뵽FIFO��
			{
				perror("Write FIFO Failed");
				close(fd);
				exit(1);
			}
			sleep(1);  // ����1��
		}

		close(fd);  // �ر�FIFO�ļ�
		return 0;
	}

	int ipc_read_fifo() 
	{
		int fd;
		int len;
		char buf[1024];

		if (mkfifo("fifo1", 0666) < 0 && errno != EEXIST) // ����FIFO�ܵ�
			perror("Create FIFO Failed");

		if ((fd = open("fifo1", O_RDONLY)) < 0)  // �Զ���FIFO
		{
			perror("Open FIFO Failed");
			exit(1);
		}

		while ((len = read(fd, buf, 1024)) > 0) // ��ȡFIFO�ܵ�
			printf("Read message: %s", buf);

		close(fd);  // �ر�FIFO�ļ�
		return 0;
	}
}