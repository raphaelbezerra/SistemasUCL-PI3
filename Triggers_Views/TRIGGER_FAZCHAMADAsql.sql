delimiter #

create trigger processa_chamada after insert on captador_chamada
for each row

BEGIN
DECLARE lido varchar(20);

SET lido = (select rf_cod from captador_chamada where id = (select max(id) from captador_chamada));

IF(lido in (select cartao_professor from RFID_PROF_CHAMADA where inicio_c > '00:00' and fim_c = '00:00')) THEN
		SET SQL_SAFE_UPDATES = 0;
        update
		CHAMADA C
		JOIN 
		AGENDAMENTO G ON G.id = C.AGENDAMENTO_id and CAST(now() AS TIME) between G.hora_ini and G.hora_fim AND cast(C.data as date) = cast(now() as date)
		JOIN
		PAUTA P ON P.id = G.PAUTA_ID
		JOIN
		PESSOA PP ON P.PROFESSOR_id = PP.id
		SET C.hora_fim = cast(now() as time)
		where PP.rfid = lido;
END IF;

IF(lido in (select cartao_professor from RFID_PROF_CHAMADA where inicio_c = '00:00')) THEN
		SET SQL_SAFE_UPDATES = 0;
        update
		CHAMADA C
		JOIN 
		AGENDAMENTO G ON G.id = C.AGENDAMENTO_id and CAST(now() AS TIME) between G.hora_ini and G.hora_fim AND cast(C.data as date) = cast(now() as date)
		JOIN
		PAUTA P ON P.id = G.PAUTA_ID
		JOIN
		PESSOA PP ON P.PROFESSOR_id = PP.id
		SET C.hora_inicio = cast(now() as time)
		where PP.rfid = lido;
END IF;
IF(lido in (select rfid from RFID_ALUNO_CHAMADA where PODE_CHAMADA = 1)) THEN
    INSERT INTO REGISTRO_CHAMADA (CHAMADA_id,PESSOA_id) VALUES((SELECT DISTINCT ID_CHAMADA FROM RFID_ALUNO_CHAMADA WHERE rfid = lido AND PODE_CHAMADA = 1),(SELECT DISTINCT PESSOA_id FROM RFID_ALUNO_CHAMADA WHERE rfid = lido AND PODE_CHAMADA = 1)) ;
/*ELSE
    SET nba = nb;*/
END IF;
END#

delimiter ;