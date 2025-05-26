CREATE TABLE user (
 user_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
 apellidos VARCHAR(64) NOT NULL,
 nombres VARCHAR(64) NOT NULL,
 email VARCHAR(64) NOT NULL,
 nivel TINYINT UNSIGNED NOT NULL,
 clave VARCHAR(128) NOT NULL,
 expira_clave DATE NOT NULL DEFAULT '2020-01-01',
 token VARCHAR(64) NULL,
 last_login DATETIME NULL,
 ip_address VARCHAR(64) NULL,
 insert_user INT UNSIGNED NULL,
 insert_datetime datetime NOT NULL,
 update_user INT UNSIGNED  NULL,
 update_datetime datetime NOT NULL,
 PRIMARY KEY (user_id),
 UNIQUE(email),
 UNIQUE(token),
 CONSTRAINT FOREIGN KEY (insert_user) REFERENCES user (user_id),
 CONSTRAINT FOREIGN KEY (update_user) REFERENCES user (user_id)
) ENGINE=InnoDB;

CREATE TABLE articulo (
  articulo_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  user_id INT UNSIGNED NOT NULL,
  titulo VARCHAR(256) NOT NULL,
  descripcion TEXT NULL,
  moneda ENUM("ARS","USS") DEFAULT "ARS" NOT NULL,
  precio DECIMAL(16,2) NOT NULL,
  en_venta ENUM("S") NULL DEFAULT NULL,
  vendido_el DATETIME NULL,
  insert_user INT UNSIGNED NOT NULL,
  insert_datetime datetime NOT NULL,
  update_user INT UNSIGNED  NOT NULL,
  update_datetime datetime NOT NULL,
  PRIMARY KEY (articulo_id),
  CONSTRAINT FOREIGN KEY (user_id) REFERENCES user (user_id),
  CONSTRAINT FOREIGN KEY (insert_user) REFERENCES user (user_id),
  CONSTRAINT FOREIGN KEY (update_user) REFERENCES user (user_id)
) ENGINE=InnoDB;

CREATE TABLE articulo_foto (
  articulo_foto_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  articulo_id INT UNSIGNED NOT NULL,
  titulo VARCHAR(256) NOT NULL,
  foto MEDIUMBLOB NOT NULL,
  foto_tipo_file VARCHAR(128) NOT NULL,
  insert_user INT UNSIGNED NOT NULL,
  insert_datetime datetime NOT NULL,
  update_user INT UNSIGNED  NOT NULL,
  update_datetime datetime NOT NULL,
  PRIMARY KEY (articulo_foto_id),
  CONSTRAINT FOREIGN KEY (articulo_id) REFERENCES articulo (articulo_id),
  CONSTRAINT FOREIGN KEY (insert_user) REFERENCES user (user_id),
  CONSTRAINT FOREIGN KEY (update_user) REFERENCES user (user_id)
) ENGINE=InnoDB;