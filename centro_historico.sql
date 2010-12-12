BEGIN;
CREATE TABLE "barrio" (
    "id" integer NOT NULL PRIMARY KEY,
    "nombre" varchar(40) NOT NULL
)
;
CREATE TABLE "titulo_encuestador" (
    "id" varchar(1) NOT NULL PRIMARY KEY,
    "abreviado" varchar(5) NOT NULL,
    "descripcion" varchar(10) NOT NULL
)
;
CREATE TABLE "encuestador" (
    "id" integer NOT NULL PRIMARY KEY,
    "titulo_id" varchar(1) REFERENCES "titulo_encuestador" ("id"),
    "nombres" varchar(50) NOT NULL,
    "apellidos" varchar(60) NOT NULL
)
;
CREATE TABLE "general" (
    "cuenta" integer NOT NULL PRIMARY KEY,
    "cuenta_corriente" varchar(12) NOT NULL,
    "numero_inventario" varchar(8),
    "direccion" varchar(150) NOT NULL,
    "numero_edificacion" varchar(80) NOT NULL,
    "zona" smallint NOT NULL,
    "manzana" smallint NOT NULL,
    "lote" smallint NOT NULL,
    "denom_edificacion" varchar(100) NOT NULL,
    "denom_historica" varchar(100) NOT NULL,
    "barrio_id" integer NOT NULL REFERENCES "barrio" ("id"),
    "encuestador_id" integer NOT NULL REFERENCES "encuestador" ("id"),
    "fecha" date,
    "catalogacion" varchar(30) NOT NULL,
    "comentario" text NOT NULL
)
;
CREATE TABLE "dimension" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "ancho" decimal NOT NULL,
    "largo" decimal NOT NULL,
    "superficie" decimal NOT NULL,
    "ocupacion" decimal NOT NULL,
    "edificabilidad" decimal NOT NULL
)
;
CREATE TABLE "edificacion" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "superficie" decimal NOT NULL,
    "superficie_total" decimal NOT NULL,
    "pisos" smallint NOT NULL,
    "edificacion" varchar(1),
    "piso_ss" smallint NOT NULL,
    "piso_1" smallint NOT NULL,
    "piso_2" smallint NOT NULL,
    "piso_3" smallint NOT NULL,
    "piso_M" smallint NOT NULL
)
;
CREATE TABLE "patio" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "estacionamiento" integer NOT NULL,
    "ocupacion" varchar(1),
    "jardin" bool NOT NULL,
    "comercio" bool NOT NULL,
    "abandonado" bool NOT NULL,
    "otros" bool NOT NULL
)
;
CREATE TABLE "acceso" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "nivel" varchar(1),
    "central" bool NOT NULL,
    "lat_izq" bool NOT NULL,
    "lat_der" bool NOT NULL,
    "esquina" bool NOT NULL,
    "galeria" bool NOT NULL,
    "modificado" bool NOT NULL
)
;
CREATE TABLE "entorno" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "vereda_material" text,
    "vereda_estado" varchar(1),
    "vereda_incidencia" varchar(1),
    "calzada_material" text,
    "calzada_estado" varchar(1),
    "calzada_incidencia" varchar(1),
    "vegetacion_material" text,
    "vegetacion_estado" varchar(1),
    "vegetacion_incidencia" varchar(1),
    "mobiliario_material" text,
    "mobiliario_estado" varchar(1),
    "mobiliario_incidencia" varchar(1),
    "otros_material" text,
    "otros_estado" varchar(1),
    "otros_incidencia" varchar(1)
)
;
CREATE TABLE "servicio" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "agua" varchar(1),
    "desague" varchar(1),
    "higiene" varchar(1),
    "lavanderias" varchar(1),
    "luz" varchar(1),
    "transporte" bool NOT NULL,
    "estudios" varchar(1),
    "recreo" varchar(1),
    "barrio" varchar(1),
    "cambio" varchar(1)
)
;
CREATE TABLE "ocupacion" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "familias" smallint NOT NULL,
    "tenencia" varchar(1),
    "mantenimiento" bool NOT NULL
)
;
CREATE TABLE "edad" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "anyo" integer,
    "elAnyo" varchar(1)
)
;
CREATE TABLE "patologia" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "mat" smallint NOT NULL,
    "tex" smallint NOT NULL,
    "col" smallint NOT NULL,
    "alt" smallint NOT NULL,
    "let" smallint NOT NULL,
    "zoc" smallint NOT NULL,
    "copi" smallint NOT NULL,
    "mol" smallint NOT NULL,
    "por" smallint NOT NULL,
    "gal" smallint NOT NULL,
    "arc" smallint NOT NULL,
    "adi" smallint NOT NULL,
    "dec" smallint NOT NULL,
    "bavo" smallint NOT NULL,
    "bare" smallint NOT NULL,
    "ale" smallint NOT NULL,
    "cor" smallint NOT NULL,
    "ant" smallint NOT NULL,
    "bal" smallint NOT NULL,
    "hor" smallint NOT NULL,
    "ite" smallint NOT NULL,
    "izi" smallint NOT NULL,
    "ias" smallint NOT NULL,
    "pis" smallint NOT NULL,
    "mur" smallint NOT NULL,
    "pil" smallint NOT NULL,
    "vig" smallint NOT NULL,
    "earc" smallint NOT NULL,
    "esc" smallint NOT NULL,
    "mat_ot" varchar(40),
    "tex_ot" varchar(40),
    "col_ot" varchar(40),
    "alt_ot" varchar(40),
    "let_ot" varchar(40),
    "zoc_ot" varchar(40),
    "copi_ot" varchar(40),
    "mol_ot" varchar(40),
    "por_ot" varchar(40),
    "gal_ot" varchar(40),
    "arc_ot" varchar(40),
    "adi_ot" varchar(40),
    "dec_ot" varchar(40),
    "bavo_ot" varchar(40),
    "bare_ot" varchar(40),
    "ale_ot" varchar(40),
    "cor_ot" varchar(40),
    "ant_ot" varchar(40),
    "bal_ot" varchar(40),
    "hor_ot" varchar(40),
    "ite_ot" varchar(40),
    "izi_ot" varchar(40),
    "ias_ot" varchar(40),
    "pis_ot" varchar(40),
    "mur_ot" varchar(40),
    "pil_ot" varchar(40),
    "vig_ot" varchar(40),
    "earc_ot" varchar(40),
    "esc_ot" varchar(40)
)
;
CREATE TABLE "tratamiento_general" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "pss_materiales" varchar(50),
    "pss_textura" varchar(50),
    "pss_color" varchar(50),
    "pss_alteraciones" bool,
    "pss_letreros" varchar(50),
    "pss_otros" bool,
    "p1_materiales" varchar(50),
    "p1_textura" varchar(50),
    "p1_color" varchar(50),
    "p1_alteraciones" bool,
    "p1_letreros" varchar(50),
    "p1_otros" bool,
    "p2_materiales" varchar(50),
    "p2_textura" varchar(50),
    "p2_color" varchar(50),
    "p2_alteraciones" bool,
    "p2_letreros" varchar(50),
    "p2_otros" bool,
    "p3_materiales" varchar(50),
    "p3_textura" varchar(50),
    "p3_color" varchar(50),
    "p3_alteraciones" bool,
    "p3_letreros" varchar(50),
    "p3_otros" bool,
    "pM_materiales" varchar(50),
    "pM_textura" varchar(50),
    "pM_color" varchar(50),
    "pM_alteraciones" bool,
    "pM_letreros" varchar(50),
    "pM_otros" bool
)
;
CREATE TABLE "fachada" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "piso_ss" smallint NOT NULL,
    "piso_1" smallint NOT NULL,
    "piso_2" smallint NOT NULL,
    "piso_3" smallint NOT NULL,
    "piso_M" smallint NOT NULL,
    "pss_otros" varchar(50) NULL,
    "p1_otros" varchar(50) NULL,
    "p2_otros" varchar(50) NULL,
    "p3_otros" varchar(50) NULL,
    "pM_otros" varchar(50) NULL
)
;
CREATE TABLE "remates" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "alero" bool NOT NULL,
    "cornisa" bool NOT NULL,
    "antepecho" bool NOT NULL,
    "balaustrada" bool NOT NULL,
    "otros" varchar(50) NOT NULL
)
;
CREATE TABLE "cubierta" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "tipo" varchar(1) NOT NULL,
    "incl_teja" bool NOT NULL,
    "incl_zinc" bool NOT NULL,
    "incl_asb" bool NOT NULL
)
;
CREATE TABLE "estructura" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "piso" varchar(50) NOT NULL,
    "muros" varchar(50) NOT NULL,
    "pilares" varchar(50) NOT NULL,
    "vigas" varchar(50) NOT NULL,
    "arcos" varchar(50) NOT NULL,
    "escalera" varchar(50) NOT NULL
)
;
CREATE TABLE "conservacion" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "uso_original" varchar(50) NOT NULL,
    "reconvertida" varchar(50) NOT NULL,
    "obra" varchar(1),
    "estado" varchar(1)
)
;
CREATE TABLE "valoracion" (
    "cuenta_id" integer NOT NULL PRIMARY KEY REFERENCES "general" ("cuenta"),
    "estilo" varchar(80) NOT NULL,
    "calificacion" varchar(1)
)
;
CREATE TABLE "tipo_imagen" (
    "id" varchar(1) NOT NULL PRIMARY KEY,
    "descripcion" varchar(8) NOT NULL
)
;
CREATE TABLE "imagen" (
    "id" integer NOT NULL PRIMARY KEY,
    "cuenta_id" integer NOT NULL REFERENCES "general" ("cuenta"),
    "titulo" varchar(50),
    "categoria_id" varchar(1) NOT NULL REFERENCES "tipo_imagen" ("id"),
    "filename" varchar(100) NOT NULL
)
;
CREATE INDEX "encuestador_titulo_id" ON "encuestador" ("titulo_id");
CREATE INDEX "general_barrio_id" ON "general" ("barrio_id");
CREATE INDEX "general_encuestador_id" ON "general" ("encuestador_id");
CREATE INDEX "entorno_cuenta_id" ON "entorno" ("cuenta_id");
CREATE INDEX "tratamiento_general_cuenta_id" ON "tratamiento_general" ("cuenta_id");
CREATE INDEX "fachada_cuenta_id" ON "fachada" ("cuenta_id");
CREATE INDEX "imagen_cuenta_id" ON "imagen" ("cuenta_id");
CREATE INDEX "imagen_categoria_id" ON "imagen" ("categoria_id");
COMMIT;
