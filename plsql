CREATE OR REPLACE FUNCTION getValorExtenso (
    valor IN NUMBER
)
RETURN VARCHAR2
IS
    TYPE t_arr IS VARRAY(19) OF VARCHAR2(30);
    TYPE t_dez IS VARRAY(9) OF VARCHAR2(30);
    TYPE t_esc IS VARRAY(4) OF VARCHAR2(30);


    unidades t_arr := t_arr(
        'um', 'dois', 'três', 'quatro',
        'cinco', 'seis', 'sete', 'oito', 'nove',
        'dez', 'onze', 'doze', 'treze', 'quatorze',
        'quinze', 'dezesseis', 'dezessete', 'dezoito', 'dezenove'
    );

    dezenas t_dez := t_dez(
        '', 'vinte', 'trinta', 'quarenta',
        'cinquenta', 'sessenta', 'setenta', 'oitenta', 'noventa'
    );

    centenas t_dez := t_dez(
        'cento', 'duzentos', 'trezentos', 
        'quatrocentos', 'quinhentos', 'seiscentos', 
        'setecentos', 'oitocentos', 'novecentos'
    );

    escalas t_esc := t_esc(
        '', 'mil', 'milhões', 'bilhões'
    );

    lv_vextenso VARCHAR2(4000);
    ln_digitos NUMBER;

    FUNCTION processa_bloco(bloco NUMBER) 
    RETURN VARCHAR2 
    IS
        lv_strBloco VARCHAR2(128) := '';
        ln_centena  NUMBER;
        ln_resto    NUMBER;
    BEGIN
        IF (bloco = 0) THEN
            return 'Zero';
        ELSIF (bloco = 100) THEN
            return 'Cem';
        END IF;

        ln_centena := ROUND(bloco / 100);
        ln_resto := MOD(bloco, 100);

        IF (ln_centena > 0) THEN
            lv_strBloco := centenas(ln_centena);
        END IF;

        IF (ln_resto = 0) THEN
            return lv_strBloco;
        ELSIF (ln_resto >= 1 AND ln_resto <= 19) THEN
            IF ln_centena > 0 THEN
                lv_strBloco  := lv_strBloco || ' e ';
            END IF;
            lv_strBloco := lv_strBloco || unidades(ln_resto);
        END IF;
        return lv_strBloco;
    END;

BEGIN
    
    ln_digitos := LENGTH(TO_CHAR(valor));
   

    lv_vextenso := processa_bloco(valor);

    RETURN lv_vextenso;
END;
/
