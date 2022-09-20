class Z {
	private:
	int x;
};

class B {
	private:
	Z x;
};

class D: public B{
	private:
	Z y;
	public:
	//ridefinizione di operator =
	D& operator=(const D& d){
		B::operator=(d); //*this implicito
		y=d.y;
		return *this;
	}
};

main(){
	
}