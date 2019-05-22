
signal a: std_logic_vector(3 downto 1);
variable X: integer;
variable Y: std_logic;
variable Z: std_logic_vector(4 downto 0);
constant b: integer := 5;
if (X = 5) and (Y = 9) and (Z<"111") then
	Z <= A;
	b = 4;
elsif (X >= 5) then
	Z <= B;
else
	Z < C;
end if;
