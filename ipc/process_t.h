#pragma once


namespace hogason {
	/*�¶�����ʾ��*/
	int orphan();

	/*��ʬ����ʾ��*/
	int zombie();

	/*ѭ��������ʬ���̣��ѻ���ʬ���̡� mainӦ���� & �ػ����̵���*/
	int zombieloop();

	/*��handler�����ӽ��̽���ʱ��SIGCHILD�źţ����������ʬ����*/
	int handle_sig();

	/*��������fork����һ���ӽ����˳���ڶ��ӽ��̳�Ϊ�¶����̣���init���̴���*/
	int fork_double();
}
