package com.prep.legacy;

public class CoinToss {
	Thread cointossThread, displayInfoThread, initThread;
	Long numberOfExperiments, heads, tails, numberofheadsinarow, previous, previousincremented;
	Boolean lastwasahead = false;
	Double error;

	CoinToss() {
		setupThreads();
		startThreads();
	}

	public synchronized void displayInfo() {
		System.out.println("Number of experiments: " + numberOfExperiments);
		System.out.println("Number of heads: " + heads);
		System.out.println("Number of heads in a row : " + previous);
		System.out.println("Number of times previous incremented : " + previousincremented);
		System.out.println("prob: " + error);
		System.out.println("**************************************");
	}

	private void setupThreads() {
		initThread = new Thread(new Runnable() {
			public void run() {
				synchronized (this) {
					numberOfExperiments = heads = tails = numberofheadsinarow = previous = previousincremented = 0L;
				}
			}
		});
		cointossThread = new Thread(new Runnable() {
			public void run() {
				synchronized (this) {
					while (true) {
						numberOfExperiments++;
						if (Math.random() < (0.01)) {
							heads++;
							if (lastwasahead)
								numberofheadsinarow++;
							lastwasahead = true;
						} else {
							tails++;
							if (numberofheadsinarow > previous) {
								previousincremented++;
								previous = numberofheadsinarow;
							}
							lastwasahead = false;
							numberofheadsinarow = 0L;
						}
						error = (Double.valueOf(heads) / Double.valueOf(numberOfExperiments));
					}
				}
			}
		});
		displayInfoThread = new Thread(new Runnable() {
			public void run() {
				while (true) {
					try {
						Thread.sleep(1000);
						displayInfo();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		});
	}

	private void startThreads() {
		initThread.start();
		try {
			initThread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		cointossThread.start();
		displayInfoThread.start();
	}

	public static void main(String[] args) {
		new CoinToss();
	}
}
