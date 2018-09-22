#ifndef _HOGASON_EPOLL_SERVER_HPP
#define _HOGASON_EPOLL_SERVER_HPP

#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>

namespace hogason
{
	namespace epoll
	{
		using ep_t = int;

		/*
		 * 1.���û�����һ���ַ��������ַ�������buffer���ַ�ͣ����buffer�У�����Ϊbuffer�ɿձ�Ϊ���գ�����ET���ض������������welcome to epoll's world������
		 * 2.֮������ٴ�ִ��epoll_wait����ʱ��Ȼbuffer�������ݿɶ������Ǹ��������Ͻڵķ�����ET�������ؾ���������epoll_wait������
		 *	���ײ�ԭ����ET�¾���fd��epitemֻ������rdlistһ�Σ���
		 * 3.�û��ٴ�����һ���ַ�������buffer�е��������࣬���������Ͻڵķ����⽫����fd״̬�ĸı䣬�Ƕ�Ӧ��epitem�ٴμ���rdlist��
		 *	�Ӷ�ʹepoll_wait���ض��������ٴ������Welcome to epoll's world������
		 */
		void et_stdin()
		{
			using std::cout;
			using std::endl;

			ep_t epfd;
			epoll_event ev;
			epoll_event events[10];	//ev����ע���¼����������ڷ���Ҫ������¼�

			epfd = epoll_create(10);
			ev.data.fd = STDIN_FILENO;
			ev.events = EPOLLIN | EPOLLET; //������״̬ͬʱ����ETģʽ
			epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);	//ע��epoll�¼�

			int nfds;
			while (true)
			{
				nfds = epoll_wait(epfd, events, 10, -1);
				for (int i = 0; i < nfds; ++i)
				{
					if (events[i].data.fd == STDIN_FILENO)
					{
						cout << "Trigger event." << endl;
					}
				}
			}
		}

		/*
		 * ������Ȼʹ��ET������ÿ�ζ��������������ٴ�MOD IN�¼������Ƿ��ֳ����ٴγ�����ѭ����Ҳ����ÿ�η��ض�������
		 * ����ע�⣬������ǽ�MOD��ΪADD������������κ�Ӱ�졣
		 * ������ÿ��ADDһ��������������epitem��ɵĺ���������һ�������֮ǰ�Ѿ�ADD��һ�Σ��ٴ�ADD����ֹ��ӣ������ڴε���ADD IN�¼��������κ�Ӱ�졣
		 */
		void et_stdin_reset()
		{
			using std::cout;
			using std::endl;

			ep_t epfd;
			epoll_event ev;
			epoll_event events[10];	//ev����ע���¼����������ڷ���Ҫ������¼�

			epfd = epoll_create(10);
			ev.data.fd = STDIN_FILENO;
			ev.events = EPOLLIN | EPOLLET; //������״̬ͬʱ����ETģʽ
			epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);	//ע��epoll�¼�

			int nfds;
			while (true)
			{
				nfds = epoll_wait(epfd, events, 10, -1);
				for (int i = 0; i < nfds; ++i)
				{
					if (events[i].data.fd == STDIN_FILENO)
					{
						cout << "Trigger event." << endl;
						ev.data.fd = STDIN_FILENO;
						ev.events = EPOLLIN | EPOLLET;                        //����ETģʽ
						epoll_ctl(epfd, EPOLL_CTL_MOD, STDIN_FILENO, &ev);    //����epoll�¼���ADD��Ч��

					}
				}
			}
		}

		/*
		 * ����������ѭ������Ϊ�û������������ݺ����ݱ�����buffer��û�б�����������LTģʽ��ÿ��epoll_wait����Ϊbuffer�ɶ����ض�������
		 * ����ÿ�ζ��������welcome to epoll's world������
		 */
		void lt_stdin()
		{
			using std::cout;
			using std::endl;

			ep_t epfd;
			epoll_event ev;
			epoll_event events[10];	//ev����ע���¼����������ڷ���Ҫ������¼�

			epfd = epoll_create(10);
			ev.data.fd = STDIN_FILENO;
			ev.events = EPOLLIN;	//Ĭ��ʹ��LTģʽ
			epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);	//ע��epoll�¼�

			int nfds;
			while (true)
			{
				nfds = epoll_wait(epfd, events, 10, -1);
				for (int i = 0; i < nfds; ++i)
				{
					if (events[i].data.fd == STDIN_FILENO)
					{
						cout << "Trigger event." << endl;
					}
				}
			}
		}

		/*
		 * ��������Ȼʹ��LTģʽ������ÿ��epoll_wait���ض�������ʱ�����Ƕ���buffer�����壩�е�����read���������Ե���buffer�ٴ���գ��´ε���epoll_wait�ͻ�������
		 * �����ܹ�ʵ����������Ҫ�Ĺ��ܡ������û��ӿ���̨���κ��������ʱ�������welcome to epoll's world����
		 */
		void lt_stdin_rd()
		{
			using std::cout;
			using std::endl;

			ep_t epfd;
			epoll_event ev;
			epoll_event events[10];	//ev����ע���¼����������ڷ���Ҫ������¼�

			epfd = epoll_create(10);
			ev.data.fd = STDIN_FILENO;
			ev.events = EPOLLIN;	//Ĭ��ʹ��LTģʽ
			epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);	//ע��epoll�¼�

			int nfds;
			while (true)
			{
				nfds = epoll_wait(epfd, events, 10, -1);
				for (int i = 0; i < nfds; ++i)
				{
					if (events[i].data.fd == STDIN_FILENO)
					{
						char buf[1024] = { 0 };
						read(STDIN_FILENO, buf, sizeof(buf));
						cout << "Trigger event." << endl;
					}
				}
			}
		}

		/*
		 * 1.���ȳ�ʼbufferΪ�գ�buffer���пռ��д����ʱ������ET����LT���Ὣ��Ӧ��epitem����rdlist������epoll_wait�ͷ���д������
		 * 2.�������׼��������Trigger stdout event.���ͻ��з�����Ϊ��׼���Ϊ����̨��ʱ�򻺳��ǡ��л��塱,���Ի��з�����buffer�е�������գ�
		 *	��Ͷ�Ӧ�ڶ�����ETģʽ��д�����ĵڶ�������������о����ݱ�������ʱ����buffer�д�д�����ݱ��ٵ�ʱ��ᴥ��fd״̬�ĸı䡣
		 *	�����´�epoll_wait�᷵��д���������ѭ��������
		 */
		void et_stdout()
		{
			using std::cout;
			using std::endl;

			ep_t epfd;
			epoll_event ev;
			epoll_event events[10];	//ev����ע���¼����������ڷ���Ҫ������¼�

			epfd = epoll_create(10);
			ev.data.fd = STDOUT_FILENO;
			ev.events = EPOLLOUT | EPOLLET; //������״̬ͬʱ����ETģʽ
			epoll_ctl(epfd, EPOLL_CTL_ADD, STDOUT_FILENO, &ev);	//ע��epoll�¼�

			int nfds;
			while (true)
			{
				nfds = epoll_wait(epfd, events, 10, -1);
				for (int i = 0; i < nfds; ++i)
				{
					if (events[i].data.fd == STDOUT_FILENO)
					{
						cout << "Trigger stdout event." << endl;
					}
				}
			}
		}

		/*
		 * �����et_stdout��ȣ��˳���ֻ�ǽ�������Ļ����Ƴ������ǿ�������ɹ���״̬��
		 * ��Ϊ��һ��epoll_wait����д�����󣬳������׼�����buffer��д�롰Trigger stdout event.����
		 * ������Ϊû��������У�����buffer�е�����һֱ���ڣ��´�epoll_wait��ʱ����Ȼ��д�ռ䵫��ETģʽ�²��ٷ���д������
		 * �����һ�ڹ���ET��ʵ�֣��������ԭ����ǵ�һ��bufferΪ�գ�����epitem����rdlist������һ�ξ������Ƴ���epitem��֮����Ȼbuffer��Ȼ��д��
		 * �������ڶ�Ӧepitem�Ѿ�����rdlist�У��Ͳ���������fd��events���ڼ���ˡ�
		 */
		void et_stdout_rm_crlf()
		{
			using std::cout;
			using std::endl;

			ep_t epfd;
			epoll_event ev;
			epoll_event events[10];	//ev����ע���¼����������ڷ���Ҫ������¼�

			epfd = epoll_create(10);
			ev.data.fd = STDOUT_FILENO;
			ev.events = EPOLLOUT | EPOLLET; //������״̬ͬʱ����ETģʽ
			epoll_ctl(epfd, EPOLL_CTL_ADD, STDOUT_FILENO, &ev);	//ע��epoll�¼�

			int nfds;
			while (true)
			{
				nfds = epoll_wait(epfd, events, 10, -1);
				for (int i = 0; i < nfds; ++i)
				{
					if (events[i].data.fd == STDOUT_FILENO)
					{
						cout << "Trigger stdout event.";
					}
				}
			}
		}
	}
}

#endif // _HOGASON_EPOLL_SERVER_HPP
