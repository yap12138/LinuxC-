#pragma once

namespace hogason 
{
	/*�����ܵ�*/
	int ipc_pipe();

	/*�����ܵ� write��*/
	int ipc_write_fifo();

	/*�����ܵ� read��*/
	int ipc_read_fifo();

	namespace sig
	{
		/*�źŷ���*/
		void sig_send();
	}

	void ipc_msg_server();

	void ipc_msg_client();
}
