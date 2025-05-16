
CREATE TABLE user (
 user_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
 apellidos VARCHAR(64) NOT NULL,
 nombres VARCHAR(64) NOT NULL,
 email VARCHAR(64) NOT NULL,
 clave VARCHAR(128) NOT NULL,
 token VARCHAR(128) NOT NULL,
 last_login DATETIME NOT NULL,
 insert_user INT UNSIGNED NOT NULL,
 insert_datetime datetime NOT NULL,
 update_user INT UNSIGNED  NOT NULL,
 update_datetime datetime NOT NULL,
 PRIMARY KEY (user_id),
 CONSTRAINT FOREIGN KEY (insert_user) REFERENCES user (user_id),
 CONSTRAINT FOREIGN KEY (update_user) REFERENCES user (user_id)
) ENGINE=InnoDB;
