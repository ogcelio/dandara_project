/*
    Minha fome vem da alma;
    Meu machado é de Assis.

    SANDER, J. C. A. - 2026
*/

#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

/**
 * MACRO: IMPORT_DATA
 * Os nomes passados como argumentos serão criados no escopo onde a macro for chamada.
 */
#define IMPORT_DATA(\
    path,\
    n_var,\
    n_regs_var,\
    cce_var,\
    ccd_var,\
    prec_var,\
    regs_arr,\
    nodes_arr,\
    q_arr,\
    st_arr,\
    ss0_arr,\
    esp_arr) \
    /* 1. Declaração dos Escalares no escopo da main */ \
    int n_var, n_regs_var; \
    double cce_var, ccd_var, prec_var; \
    cJSON *_root_json = NULL; \
    { \
        FILE *_f = fopen(path, "rb"); \
        if (!_f) { perror("Erro ao abrir arquivo"); exit(1); } \
        fseek(_f, 0, SEEK_END); long _sz = ftell(_f); fseek(_f, 0, SEEK_SET); \
        char *_buf = (char *)malloc(_sz + 1); \
        if (fread(_buf, 1, _sz, _f) != (size_t)_sz) { fclose(_f); free(_buf); exit(1); } \
        fclose(_f); _buf[_sz] = '\0'; \
        _root_json = cJSON_Parse(_buf); \
        free(_buf); \
        if (!_root_json) { fprintf(stderr, "Erro no parse JSON\n"); exit(1); } \
    } \
    /* 2. Atribuição dos valores aos escalares recém-criados */ \
    n_var = cJSON_GetObjectItemCaseSensitive(_root_json, "N")->valueint; \
    n_regs_var = cJSON_GetObjectItemCaseSensitive(_root_json, "NUM_REGS")->valueint; \
    cce_var = cJSON_GetObjectItemCaseSensitive(_root_json, "CCE")->valuedouble; \
    ccd_var = cJSON_GetObjectItemCaseSensitive(_root_json, "CCD")->valuedouble; \
    prec_var = cJSON_GetObjectItemCaseSensitive(_root_json, "PREC")->valuedouble; \
    /* 3. Declaração das VLAs (Arrays de tamanho variável) na Pilha */ \
    int regs_arr[n_regs_var]; \
    int nodes_arr[n_regs_var]; \
    double q_arr[n_regs_var]; \
    double st_arr[n_regs_var]; \
    double ss0_arr[n_regs_var]; \
    double esp_arr[n_regs_var]; \
    { \
        cJSON *_it; int _i; \
        cJSON *_o_regs = cJSON_GetObjectItemCaseSensitive(_root_json, "REGS"); \
        _i = 0; cJSON_ArrayForEach(_it, _o_regs) { if(_i < n_regs_var) regs_arr[_i++] = _it->valueint; } \
        cJSON *_o_nodes = cJSON_GetObjectItemCaseSensitive(_root_json, "NUM_NODES"); \
        _i = 0; cJSON_ArrayForEach(_it, _o_nodes) { if(_i < n_regs_var) nodes_arr[_i++] = _it->valueint; } \
        cJSON *_o_q = cJSON_GetObjectItemCaseSensitive(_root_json, "Q"); \
        _i = 0; cJSON_ArrayForEach(_it, _o_q) { if(_i < n_regs_var) q_arr[_i++] = _it->valuedouble; } \
        cJSON *_o_st = cJSON_GetObjectItemCaseSensitive(_root_json, "SIGMA_T"); \
        _i = 0; cJSON_ArrayForEach(_it, _o_st) { if(_i < n_regs_var) st_arr[_i++] = _it->valuedouble; } \
        cJSON *_o_ss0 = cJSON_GetObjectItemCaseSensitive(_root_json, "SIGMA_S0"); \
        _i = 0; cJSON_ArrayForEach(_it, _o_ss0) { if(_i < n_regs_var) ss0_arr[_i++] = _it->valuedouble; } \
        cJSON *_o_esp = cJSON_GetObjectItemCaseSensitive(_root_json, "ESP_REGS"); \
        _i = 0; cJSON_ArrayForEach(_it, _o_esp) { if(_i < n_regs_var) esp_arr[_i++] = _it->valuedouble; } \
    } \
    cJSON_Delete(_root_json);

/* Função de salvamento */
static inline void
SAVE_OUTPUT(
    const char *path,
    int N,
    int ITERATION,
    int TOTAL_NODES,
    int NUM_REGS,
    double FI[TOTAL_NODES + 1],
    double ABS_RATE[NUM_REGS],
    double ESCAPE_RATE[2],
    double PSI[(TOTAL_NODES + 1) * N])
{
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "iteration", ITERATION);
    cJSON_AddItemToObject(root, "fi", cJSON_CreateDoubleArray(FI, TOTAL_NODES + 1));
    cJSON_AddItemToObject(root, "abs_rate", cJSON_CreateDoubleArray(ABS_RATE, NUM_REGS));
    cJSON_AddItemToObject(root, "escape_rate", cJSON_CreateDoubleArray(ESCAPE_RATE, 2));

    cJSON *m = cJSON_CreateArray();
    for (int i = 0; i < TOTAL_NODES + 1; i++) {
        cJSON_AddItemToArray(m, cJSON_CreateDoubleArray(&PSI[i * N], N));
    }

    cJSON_AddItemToObject(root, "psi", m);

    char *s = cJSON_PrintUnformatted(root);
    if (s) {
        FILE *f = fopen(path, "w");
        if (f) {
            fputs(s, f);
            fclose(f);
        }
        free(s);
    }
    cJSON_Delete(root);
}

#endif
