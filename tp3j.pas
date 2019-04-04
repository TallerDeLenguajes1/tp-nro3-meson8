 program tp2 ;
 var unidades: integer;
   pago: integer;
          begin
  writeln ('Ingrese cantidad de unidades');
  readln (unidades);
  if (0<unidades) and (unidades<100) then
  
          begin
                          pago:= unidades*100;

if unidades:=200 then
	      begin
                  pago:= (unidades-100)*200+(100*100);

end
else
	      begin
            pago:=(unidades-200)*300+(10000+(100*200));
end
writeln ('el pago del jornal sera')
writeln pago
end;




