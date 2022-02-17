package il.co.ilrd.hello_world;

import java.util.*;
import java.lang.Runtime;

class my100k {
	public static void main(String[] args) {

		List<int[]> listOfArrayOfInts = new ArrayList<>();

		Runtime rt = Runtime.getRuntime();
		long Total = rt.totalMemory();
		long Free = rt.freeMemory();

		int i = 0;
		int j = 0;

		while (true) {
			int[] arr = new int[100000];
			for (j = 0; j < 100000; ++j) {
				arr[j] = j;
			}
			listOfArrayOfInts.add(arr);
			Total = rt.totalMemory();
			Free = rt.freeMemory();
			System.out.println("num is " + i + " available mem " + Free + " total mem " + Total);
		}
	}
}