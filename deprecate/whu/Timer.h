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
		 * @param period 执行的时间间隔
		 * @param exec_func 每隔一段时间调用，返回值指明Timer要不要继续
		 * @param param 传给exec_fucn的参数
		 * @param 是否自动启动
		 */
		Timer(int period,bool(*exec_func)(void* p),void* param,bool auto_start);
		/**
		 * @brief 启动Timer
		 * @return 如果Timer不可用则返回false
		 */
		bool start();
		/**
		 * @breif 停止Timer，这个需要在其他线程调用，因为Timer执行不会创建新的线程
		 * 因此会阻塞
		 */
		void stop();
		/**
		 * @brief 一个简单的线程挂起实现，一段时间后继续执行下面的代码
		 */
		static void sleep(int sleep_time);
	}
}
#endif // _TK_TIMER_H_
