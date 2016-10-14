DELIMITER $$
CREATE TRIGGER insert_chamada AFTER INSERT ON AGENDAMENTO 
FOR EACH ROW BEGIN
DECLARE ini date;
DECLARE fim date;
SET fim = NEW.data_fim;
BEGIN 
WHILE ini <= fim DO 
 INSERT INTO CHAMADA (AGENDAMENTO_id,data,hora_inicio,hora_fim) values (NEW.ID,ini, '00:00', '00:00');
 SET ini = date_add(ini,interval 1 day);
 END WHILE;
 END;
 SET SQL_SAFE_UPDATES = 0;
 DELETE
 from
 CHAMADA WHERE
 weekday(data) <> (SELECT dia_semana FROM AGENDAMENTO WHERE AGENDAMENTO.id = CHAMADA.AGENDAMENTO_id);
 END;