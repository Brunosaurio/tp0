#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = log_create("tp0.log", "Cliente", true, log_level_from_string("INFO"));

	// Usando el logger creado previamente

	// Escribi: "Hola! Soy un log"

	log_info(logger, "Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = config_create("cliente.config");
	if (config == NULL) {
		log_info(logger, "No se pudo iniciar la config");
		exit(-1);
	}
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	ip = config_get_string_value(config, "IP");
	valor = config_get_string_value(config, "CLAVE");
	puerto = config_get_string_value(config, "PUERTO");
	// Loggeamos el valor de config
	log_info(logger, valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while(strcmp(leido,"") != 0){
		
		log_info(logger, leido);
		free(leido);
		leido = readline("> ");
	}
	free(leido);
	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete
	printf("Escriba los mensajes a enviar:");
	leido = readline("> ");
	if(strcmp(leido,"") != 0){
		paquete = crear_paquete();
		agregar_a_paquete(paquete,leido,string_length(leido) + 1);
	}
	while(strcmp(leido,"") != 0){
		free(leido);
		leido = readline("> ");
		agregar_a_paquete(paquete,leido,string_length(leido) + 1);
	}
	enviar_paquete(paquete,conexion);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
