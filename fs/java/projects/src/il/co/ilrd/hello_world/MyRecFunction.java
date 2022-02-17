package il.co.ilrd.hello_world;

class MyRecFunc {
	public static void main(String[] args) {
		int number_of_frames = 0;
		foo(number_of_frames);

	}

	public static void foo(int number_of_frames) {
		if (number_of_frames == 10774) {
			return;
		}
		++number_of_frames;
		System.out.println(number_of_frames);
		foo(number_of_frames);
	}
}