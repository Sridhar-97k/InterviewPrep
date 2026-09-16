package com.prep.legacy;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumer {
	private static final int BUFFER_SIZE = 5;
	private static final int[] buffer = new int[BUFFER_SIZE];
	private static int in = 0, out = 0, count = 0;
	private static final Lock lock = new ReentrantLock();
	private static final Condition notFull = lock.newCondition();
	private static final Condition notEmpty = lock.newCondition();

	public static void main(String[] args) {
		Thread producer = new Thread(ProducerConsumer::producer);
		Thread consumer = new Thread(ProducerConsumer::consumer);
		Thread someRandom = new Thread(ProducerConsumer::printSomethingRandom);
		consumer.start();
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		producer.start();
	}

	private static void printSomethingRandom() {
		System.out.println("Something random");
	}

	private static void producer() {
		while (true) {
			int item = (int) (Math.random() * 100);
			lock.lock();
			try {
				while (count == BUFFER_SIZE)
					notFull.await();
				buffer[in] = item;
				System.out.println("Produced: " + item + " at " + in);
				in = (in + 1) % BUFFER_SIZE;
				System.out.println("In variable is " + in);
				count++;
				notEmpty.signal();
			} catch (InterruptedException e) {
				e.printStackTrace();
			} finally {
				lock.unlock();
			}
			try {
				Thread.sleep(200);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	private static void consumer() {
		while (true) {
			lock.lock();
			try {
				while (count == 0) {
					System.out.println("The buffer is empty now");
					notEmpty.await();
				}
				int item = buffer[out];
				System.out.println("Consumed: " + item + " at " + out);
				out = (out + 1) % BUFFER_SIZE;
				System.out.println("Out variable is " + out);
				count--;
				notFull.signal();
			} catch (InterruptedException e) {
				e.printStackTrace();
			} finally {
				lock.unlock();
			}
			try {
				Thread.sleep(200);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
