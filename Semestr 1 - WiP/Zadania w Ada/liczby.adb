with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;


procedure liczby is
	s : integer := 0;
	w : integer := 0;
begin
	for i in 2..1000 loop
		for k in 1..(i-1) loop
			if (i rem k = 0) then
				s := s + k;
			end if;
		end loop;
		if s = i then
			Put(i,3);
			Put(" to liczba doskonala");
			New_Line;
		elsif s < 1000 then
			for l in 1..(s-1) loop
				if (s rem l = 0) then
					w := w + l;
				end if;
			end loop;
			if w = i and w < s then
				Put(i,3);
				Put(" i ");
				Put(s,3);
				Put(" to liczby zaprzyjaznione");
				New_Line;
			end if;
			w := 0;
		end if;
		s := 0;
	end loop;
end liczby;

