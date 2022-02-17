package il.co.ilrd.hello_world;

class MySecondClass{
	
	static void foo1()
	{
		System.out.println("hello, i am foo1");
	}
	
	void foo2()
	{
		System.out.println("hello, i am foo2");
	}	
	
	public static void main (String args[])
	{
		foo1();
		MySecondClass myClass = new MySecondClass();
		
		myClass.foo2();
	}
}