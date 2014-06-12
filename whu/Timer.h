#ifndef _TK_TIMER_H_
#define _TK_TIMER_H_

namespace whu{
	/**
	 * @class Timer Timer.h
	 * @brief a simpler timer for executing a function periodically
	 */
	class Timer{
	private:
		int interval; /*!< executing period */
		bool valid; /*!< timer is valid */
	public:
		/**
		 * @brief construct function
		 * @param period ִ�е�ʱ����
		 * @param exec_func ÿ��һ��ʱ����ã�����ֵָ��TimerҪ��Ҫ����
		 * @param param ����exec_fucn�Ĳ���
		 * @param �Ƿ��Զ�����
		 */
		Timer(int period,bool(*exec_func)(void* p),void* param,bool auto_start);
		/**
		 * @brief ����Timer
		 * @return ���Timer�������򷵻�false
		 */
		bool start();
		/**
		 * @breif ֹͣTimer�������Ҫ�������̵߳��ã���ΪTimerִ�в��ᴴ���µ��߳�
		 * ��˻�����
		 */
		void stop();
		/**
		 * @brief һ���򵥵��̹߳���ʵ�֣�һ��ʱ������ִ������Ĵ���
		 */
		static void sleep(int sleep_time);
	}
}
#endif // _TK_TIMER_H_
