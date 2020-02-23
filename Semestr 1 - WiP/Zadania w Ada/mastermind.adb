with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Mastermind is
	Macierz_Mozliwosci : array (Positive range 1..12, Positive range 1..1296, Positive range 1..4) of Integer;
	Liczba_Pytan : Integer := 1;
	Mozliwosci : Integer := 1296;
	Nowe_Mozliwosci : Integer := 0;
	Czerwone : Integer := 0;
	Biale : Integer := 0;
	Licznik_Czerwonych : Integer := 0;
	Licznik_Bialych : Integer := 0;
	Licznik_Liczb : Integer := 0;
	Licznik_Obecnosci : Integer := 0;
	b : Integer := 1;
begin
	for i in 0..(Mozliwosci-1) loop
		Macierz_Mozliwosci(b, i+1, 4) := 1 + i rem 6;
		Macierz_Mozliwosci(b, i+1, 3) := 1 + ((i - i rem 6)/ 6) rem 6;
		Macierz_Mozliwosci(b, i+1, 2) := 1 + ((((i - i rem 6)/ 6) - ((i - i rem 6)/ 6) rem 6)/ 6) rem 6;
		Macierz_Mozliwosci(b, i+1, 1) := 1 + ((((((i - i rem 6)/ 6) - ((i - i rem 6)/ 6) rem 6)/ 6) - ((((i - i rem 6)/ 6) - ((i - i rem 6)/ 6) rem 6)/ 6) rem 6)/ 6) rem 6;
	end loop;
	loop
		Put("Pytanie ");
		Put(Liczba_Pytan,1);
		New_Line;
		Liczba_Pytan := Liczba_Pytan + 1;
		for i in 1..4 loop
			Put("[");
			Put(Macierz_Mozliwosci(b,1,i),1);			
			Put("]");
		end loop;
		Put("?");
		New_Line;
		Put("Czerwone : ");
		Get(Czerwone);
		Put("   Białe : ");
		Get(Biale);
		if Czerwone = 4 then
			Put("Wygrałem w ");
			Put(Liczba_Pytan-1,1);
			Put(" pytań");
			New_Line;
			exit;
		end if;
		for k in 2..Mozliwosci loop
			for j in 1..4 loop
				if Macierz_Mozliwosci(b,k,j) = Macierz_Mozliwosci(b,1,j) then
					Licznik_Czerwonych := Licznik_Czerwonych + 1;
				end if;
			end loop;
			for i in 1..6 loop
				for j in 1..4 loop
					if Macierz_Mozliwosci(b,1,j) = i and Macierz_Mozliwosci(b,k,j) /= Macierz_Mozliwosci(b,1,j) then
						Licznik_Liczb := Licznik_Liczb + 1;
					end if;
				end loop;
				for j in 1..4 loop
					if Macierz_Mozliwosci(b,k,j) = i and Macierz_Mozliwosci(b,k,j) /= Macierz_Mozliwosci(b,1,j) and Licznik_Obecnosci < Licznik_Liczb and Licznik_Liczb > 0 then
						Licznik_Obecnosci := Licznik_Obecnosci + 1;
					end if;
				end loop;
				Licznik_Bialych := Licznik_Bialych + Licznik_Obecnosci;
				Licznik_Obecnosci := 0;
				Licznik_Liczb := 0;
			end loop;
			if Licznik_Czerwonych = Czerwone and Licznik_Bialych = Biale then
				Nowe_Mozliwosci := Nowe_Mozliwosci + 1;
				for j in 1..4 loop
					Macierz_Mozliwosci(b+1,Nowe_Mozliwosci,j) := Macierz_Mozliwosci(b,k,j);
				end loop;
			end if;
			Licznik_Czerwonych := 0;
			Licznik_Bialych := 0;
		end loop;
		b := b + 1;
		Mozliwosci := Nowe_Mozliwosci;
		if Mozliwosci = 0 then
			Put_Line("Oszukujesz! Albo popełniłeś błąd :P Zacznij jeszcze raz!");
			exit;
		end if;
		Nowe_Mozliwosci := 0;
	end loop;
end Mastermind;
