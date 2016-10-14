SELECT
PE.rfid,
CASE
	WHEN C.hora_inicio > '00:00' and C.hora_fim = '00:00'
    THEN 1
    ELSE 0
END AS 'CHAMADA'
FROM
PESSOA_PAUTA PP	
JOIN
AGENDAMENTO A ON A.PAUTA_id = PP.PAUTA_id
JOIN
CHAMADA C ON C.AGENDAMENTO_id = A.id 
JOIN
ALUNO AL ON AL.PESSOA_id = PP.PESSOA_id
JOIN
PESSOA PE ON PE.id = PP.PESSOA_id
WHERE
CAST(C.DATA AS DATE) = DATE_ADD(CAST(now() AS DATE),INTERVAL 0 DAY);

/*select
*
FROM
CHAMADA
WHERE
CAST(DATA AS DATE) = CAST(NOW() AS DATE)*/