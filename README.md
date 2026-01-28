# Mercado Dios Me Libre

Sistema de marketplace personal siguiendo estándares PSR-4.

## 📁 Estructura del Proyecto

```
/
├── config/                      # Configuración de la aplicación
│   └── database.php            # Configuración de base de datos y constantes
│
├── public/                      # Document root (único directorio accesible vía web)
│   ├── index.php               # Página principal
│   ├── *.php                   # Controladores públicos
│   ├── css/                    # Estilos
│   ├── js/                     # JavaScript
│   └── images/                 # Imágenes públicas
│
├── resources/views/             # Plantillas/Vistas
│   ├── layouts/                # Layouts compartidos
│   ├── articulo/               # Vistas de artículos
│   └── *.php                   # Vistas principales
│
├── src/                        # Código fuente PSR-4 (namespace: App\)
│   ├── Controller/             # Modelos y lógica de negocio
│   ├── Database/               # Capa de base de datos
│   ├── Mail/                   # Servicios de correo
│   └── Util/                   # Utilidades
│
├── lib/adodb/                  # ADOdb (biblioteca externa)
├── logs/                       # Archivos de log
├── tmp/                        # Archivos temporales
└── vendor/                     # Dependencias de Composer
```

## 🚀 Instalación

1. **Instalar dependencias**: `composer install`
2. **Configurar base de datos**: Editar `config/database.php`
3. **Configurar servidor**: Document root debe apuntar a `/public/`
4. **Permisos**: `chmod -R 755 logs/ tmp/`

## 🏗️ Arquitectura PSR-4

- **Namespace base**: `App\`
- **Autoloading**: Composer PSR-4
- **Document root**: `/public/` (único accesible vía web)
- **Vistas**: `/resources/views/`
- **Config**: `/config/` (fuera de document root)

## 📦 Stack Tecnológico

- PHP >= 7.4
- MySQL/MariaDB
- Composer
- PHPMailer ^6.10
- ADOdb

## En internet

https://www.mercadodiosmelibre.com.ar

---
Desarrollado por Julio Tuozzo
