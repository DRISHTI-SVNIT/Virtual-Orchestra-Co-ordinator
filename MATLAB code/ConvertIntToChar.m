function[returnstring] = ConvertIntToChar(coordinate)
quotient=coordinate;
remainder=coordinate;
i=1;
while quotient>9
remainder=mod(quotient,10);
quotient=quotient/10;
string(i)=char(remainder+48);
i=i+1;
end
string(i)=char(quotient+48);
j=1;
while i>0
returnstring(i)=string(j);
i=i-1;
j=j+1;
end
end