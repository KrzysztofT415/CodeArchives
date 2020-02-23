with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Float_Text_IO; use Ada.Float_Text_IO;

procedure nierownosc is
	s : float := 1.0;
	n : integer := 1;
begin
	while s <= 10.0 loop
		n := n + 1;
		s := s + (1.0 / float(n));
	end loop;
	Put("Najmniejsze takie n: ");
	New_Line;
	Put(n);
end nierownosc;
