
typedef struct
{
    long int dni;
    int idTramite;
    int turno;
}eTramite;

eTramite* tramite_newTramite();
eTramite* tramite_turnoUrgente(int numTurno);
eTramite* tramite_turnoRegular(int numTurno);
void tramite_siguiente(ArrayList* listaUrgente, ArrayList* listaRegular, ArrayList* listaAtendido);
void tramite_listarPendientes(ArrayList* listaUrgente, ArrayList* listaRegular);

int tramite_ordenarDNI(void*, void*);
