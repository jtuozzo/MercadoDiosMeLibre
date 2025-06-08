CREATE TABLE siguiendo (
  siguiendo_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  user_id INT UNSIGNED NOT NULL,
  siguiendo_a INT UNSIGNED NOT NULL,
  activo ENUM('S') NULL DEFAULT NULL,
  avisar_novedades ENUM('S') NULL DEFAULT NULL,
  insert_datetime datetime NOT NULL,
  update_datetime datetime NOT NULL,
  PRIMARY KEY (siguiendo_id),
  UNIQUE (user_id, siguiendo_a),
  CONSTRAINT FOREIGN KEY (user_id) REFERENCES user (user_id),
  CONSTRAINT FOREIGN KEY (siguiendo_a) REFERENCES user (user_id) 
) ENGINE=InnoDB;

HASTA ACÁ EN PRODUCCIÓN