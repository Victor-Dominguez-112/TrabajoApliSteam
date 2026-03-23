-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 23-03-2026 a las 06:38:39
-- Versión del servidor: 10.4.32-MariaDB
-- Versión de PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `epsteam`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `biblioteca`
--

CREATE TABLE `biblioteca` (
  `id_biblioteca` int(11) NOT NULL,
  `id_usuario` int(11) NOT NULL,
  `id_juego` int(11) NOT NULL,
  `id_detalle` int(11) NOT NULL,
  `fecha_adquisicion` date NOT NULL,
  `tiempo_jugado_minutos` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `biblioteca`
--

INSERT INTO `biblioteca` (`id_biblioteca`, `id_usuario`, `id_juego`, `id_detalle`, `fecha_adquisicion`, `tiempo_jugado_minutos`) VALUES
(1, 1, 1, 1, '2026-03-21', 121),
(2, 1, 19, 2, '2026-03-21', 121),
(3, 102, 1, 3, '2026-03-21', 121),
(4, 102, 19, 4, '2026-03-21', 121),
(5, 102, 5, 5, '2026-03-22', 121),
(6, 2, 3, 6, '2026-03-22', 121),
(7, 2, 1, 10, '2026-03-22', 42),
(8, 2, 5, 11, '2026-03-22', 42),
(9, 2, 6, 12, '2026-03-22', 42),
(10, 2, 4, 13, '2026-03-22', 37),
(11, 2, 8, 14, '2026-03-22', 37),
(12, 2, 15, 15, '2026-03-22', 27),
(13, 2, 14, 16, '2026-03-22', 21),
(14, 2, 13, 17, '2026-03-22', 21),
(15, 2, 28, 18, '2026-03-22', 16),
(16, 2, 27, 19, '2026-03-22', 16),
(17, 2, 19, 20, '2026-03-22', 16),
(18, 2, 42, 21, '2026-03-22', 16),
(19, 2, 43, 22, '2026-03-22', 16),
(20, 2, 105, 23, '2026-03-22', 16),
(21, 2, 104, 24, '2026-03-22', 16),
(22, 2, 89, 25, '2026-03-22', 16),
(23, 2, 84, 26, '2026-03-22', 12);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `categoria`
--

CREATE TABLE `categoria` (
  `id_categoria` int(11) NOT NULL,
  `nombre_categoria` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `categoria`
--

INSERT INTO `categoria` (`id_categoria`, `nombre_categoria`) VALUES
(1, 'Un jugador'),
(2, 'Multijugador en línea'),
(3, 'Logros'),
(4, 'Soporte mando'),
(5, 'Cooperativo'),
(6, 'Realidad Virtual'),
(7, 'Multijugador local'),
(8, 'MMO'),
(9, 'PvP en línea'),
(10, 'Cooperativo en línea'),
(11, 'Cooperativo local'),
(12, 'Guardado en la nube'),
(13, 'Juego cruzado (Cross-play)');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `clasificacion_edad`
--

CREATE TABLE `clasificacion_edad` (
  `id_clasificacion` int(11) NOT NULL,
  `codigo` varchar(10) NOT NULL,
  `descripcion` varchar(255) DEFAULT NULL,
  `edad_minima` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `clasificacion_edad`
--

INSERT INTO `clasificacion_edad` (`id_clasificacion`, `codigo`, `descripcion`, `edad_minima`) VALUES
(1, 'E', 'Todos', 0),
(2, 'T', 'Adolescentes', 13),
(3, 'M', 'Maduro', 17),
(4, 'AO', 'Solo Adultos', 18);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `compra`
--

CREATE TABLE `compra` (
  `id_compra` int(11) NOT NULL,
  `id_usuario` int(11) NOT NULL,
  `fecha_compra` date NOT NULL,
  `total_pagado` decimal(10,2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `compra`
--

INSERT INTO `compra` (`id_compra`, `id_usuario`, `fecha_compra`, `total_pagado`) VALUES
(1, 1, '2026-03-21', 0.00),
(2, 1, '2026-03-21', 0.00),
(3, 102, '2026-03-21', 0.00),
(4, 102, '2026-03-21', 0.00),
(5, 102, '2026-03-22', 113.99),
(6, 2, '2026-03-22', 599.00),
(7, 2, '2026-03-22', 712.99),
(8, 2, '2026-03-22', 712.99),
(9, 2, '2026-03-22', 712.99),
(10, 2, '2026-03-22', 1399.00),
(11, 2, '2026-03-22', 1348.99),
(12, 2, '2026-03-22', 559.98),
(13, 2, '2026-03-22', 0.00),
(14, 2, '2026-03-22', 1218.99),
(15, 2, '2026-03-22', 263.98),
(16, 2, '2026-03-22', 113.99),
(17, 2, '2026-03-22', 149.99);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `desarrollador`
--

CREATE TABLE `desarrollador` (
  `id_desarrollador` int(11) NOT NULL,
  `nombre_empresa` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `desarrollador`
--

INSERT INTO `desarrollador` (`id_desarrollador`, `nombre_empresa`) VALUES
(1, 'Riot Games'),
(2, 'Valve'),
(3, 'CD Projekt Red'),
(4, 'Bandai Namco'),
(5, 'Rockstar North'),
(6, 'Ubisoft'),
(7, 'Electronic Arts'),
(8, 'Square Enix'),
(9, 'Capcom'),
(10, 'Digital Extremes'),
(11, 'Supergiant Games'),
(12, 'Team Cherry'),
(13, 'Re-Logic'),
(14, 'Studio MDHR'),
(15, 'Toby Fox'),
(16, 'Playdead'),
(17, 'Mobius Digital'),
(18, 'Motion Twin'),
(19, 'ZA/UM'),
(20, 'Larian Studios'),
(21, 'Remedy Entertainment'),
(22, 'Kojima Productions'),
(23, 'FromSoftware'),
(24, 'Ryu Ga Gotoku Studio'),
(25, 'Atlus'),
(100, 'Nova Studios');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `detalle_compra`
--

CREATE TABLE `detalle_compra` (
  `id_detalle` int(11) NOT NULL,
  `id_compra` int(11) NOT NULL,
  `id_juego` int(11) NOT NULL,
  `precio_unitario` decimal(10,2) NOT NULL,
  `id_usuario_destino` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `detalle_compra`
--

INSERT INTO `detalle_compra` (`id_detalle`, `id_compra`, `id_juego`, `precio_unitario`, `id_usuario_destino`) VALUES
(1, 1, 1, 0.00, NULL),
(2, 2, 19, 0.00, NULL),
(3, 3, 1, 0.00, NULL),
(4, 4, 19, 0.00, NULL),
(5, 5, 5, 113.99, NULL),
(6, 6, 3, 599.00, NULL),
(7, 7, 1, 0.00, NULL),
(8, 7, 5, 113.99, NULL),
(9, 7, 6, 599.00, NULL),
(10, 8, 1, 0.00, NULL),
(11, 8, 5, 113.99, NULL),
(12, 8, 6, 599.00, NULL),
(13, 9, 4, 113.99, NULL),
(14, 9, 8, 599.00, NULL),
(15, 10, 15, 1399.00, NULL),
(16, 11, 14, 149.99, NULL),
(17, 11, 13, 1199.00, NULL),
(18, 12, 28, 279.99, NULL),
(19, 12, 27, 279.99, NULL),
(20, 13, 19, 0.00, NULL),
(21, 14, 42, 1199.00, NULL),
(22, 14, 43, 19.99, NULL),
(23, 15, 105, 149.99, NULL),
(24, 15, 104, 113.99, NULL),
(25, 16, 89, 113.99, NULL),
(26, 17, 84, 149.99, NULL);

--
-- Disparadores `detalle_compra`
--
DELIMITER $$
CREATE TRIGGER `trg_aumentar_jugadores` AFTER INSERT ON `detalle_compra` FOR EACH ROW BEGIN
    UPDATE Videojuego 
    SET jugadores_activos = jugadores_activos + 1 
    WHERE id_juego = NEW.id_juego;
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `editor`
--

CREATE TABLE `editor` (
  `id_editor` int(11) NOT NULL,
  `nombre_editor` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `editor`
--

INSERT INTO `editor` (`id_editor`, `nombre_editor`) VALUES
(1, 'Riot Games'),
(2, 'Valve'),
(3, 'CD Projekt'),
(4, 'Bandai Namco'),
(5, 'Rockstar Games'),
(6, 'Ubisoft'),
(7, 'Electronic Arts'),
(8, 'Square Enix'),
(9, 'Capcom'),
(10, 'Digital Extremes'),
(11, 'Devolver Digital'),
(12, 'Annapurna Interactive'),
(13, 'Team17'),
(14, 'Raw Fury'),
(15, 'Chucklefish'),
(16, 'Focus Entertainment'),
(17, '505 Games'),
(18, 'Paradox Interactive'),
(19, 'SEGA'),
(20, 'PlayStation PC'),
(21, 'Xbox Game Studios'),
(22, 'Warner Bros Games'),
(23, 'THQ Nordic'),
(24, 'Deep Silver'),
(25, 'Private Division'),
(26, 'tinyBuild'),
(27, 'Curve Games'),
(28, 'Playism'),
(29, 'XSEED Games'),
(30, 'Nicalis'),
(31, 'Adult Swim Games'),
(32, 'Finji'),
(33, 'Kowloon Nights'),
(34, 'Fellow Traveller'),
(35, 'New Blood Interactive'),
(36, 'Humble Games'),
(37, 'Saber Interactive'),
(38, 'D3 Publisher'),
(39, 'Spike Chunsoft'),
(40, 'Marvelous'),
(41, 'Koei Tecmo'),
(100, 'Nova Publishing');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `etiqueta`
--

CREATE TABLE `etiqueta` (
  `id_etiqueta` int(11) NOT NULL,
  `nombre_etiqueta` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `etiqueta`
--

INSERT INTO `etiqueta` (`id_etiqueta`, `nombre_etiqueta`) VALUES
(1, 'Multijugador'),
(2, 'Mundo Abierto'),
(3, 'Anime'),
(4, 'Competitivo'),
(5, 'Historia Rica'),
(6, 'Difícil'),
(7, 'Realidad Virtual'),
(8, 'Relajante'),
(9, 'Zombies'),
(10, 'Post-apocalíptico'),
(11, 'Cyberpunk'),
(12, 'Espacio'),
(13, 'Buena banda sonora'),
(14, 'Gestión de recursos'),
(15, 'Hack and Slash'),
(16, 'Ciencia ficción'),
(17, 'Fantasía Oscura'),
(18, 'Magia'),
(19, 'Piratas'),
(20, 'Ninja / Samurái'),
(21, 'Misterio'),
(22, 'Humor negro'),
(23, 'Física divertida'),
(24, 'Retro / Pixel Art'),
(25, 'Para toda la familia');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `genero`
--

CREATE TABLE `genero` (
  `id_genero` int(11) NOT NULL,
  `nombre_genero` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `genero`
--

INSERT INTO `genero` (`id_genero`, `nombre_genero`) VALUES
(1, 'Shooter'),
(2, 'RPG'),
(3, 'Acción'),
(4, 'Aventura'),
(5, 'Lucha'),
(6, 'Terror / Horror'),
(7, 'Carreras'),
(8, 'Simulación'),
(9, 'Estrategia'),
(10, 'Plataformas'),
(11, 'Puzzle'),
(12, 'Deportes'),
(13, 'Sandbox'),
(14, 'Roguelike / Roguelite'),
(15, 'Sigilo'),
(16, 'Metroidvania'),
(17, 'Musou'),
(18, 'Supervivencia');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `juego_categoria`
--

CREATE TABLE `juego_categoria` (
  `id_juego` int(11) NOT NULL,
  `id_categoria` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `juego_categoria`
--

INSERT INTO `juego_categoria` (`id_juego`, `id_categoria`) VALUES
(1, 2),
(1, 9),
(1, 13),
(2, 1),
(2, 4),
(3, 1),
(3, 4),
(4, 1),
(4, 10),
(4, 11),
(5, 1),
(5, 4),
(6, 1),
(6, 2),
(6, 9),
(7, 1),
(7, 2),
(7, 4),
(8, 1),
(8, 10),
(9, 1),
(9, 2),
(9, 9),
(10, 2),
(10, 5),
(10, 10),
(11, 1),
(11, 4),
(12, 1),
(12, 4),
(13, 1),
(13, 2),
(13, 10),
(14, 1),
(14, 11),
(15, 1),
(15, 4),
(16, 1),
(16, 6),
(17, 7),
(17, 10),
(17, 11),
(18, 1),
(18, 2),
(18, 7),
(18, 9),
(19, 2),
(19, 5),
(19, 8),
(19, 10),
(19, 13),
(20, 1),
(20, 4),
(21, 1),
(21, 4),
(22, 1),
(22, 4),
(23, 1),
(23, 4),
(24, 1),
(24, 4),
(25, 1),
(25, 4),
(26, 1),
(26, 4),
(27, 1),
(27, 4),
(28, 1),
(28, 4),
(28, 5),
(28, 10),
(29, 1),
(29, 4),
(30, 1),
(30, 4),
(31, 1),
(31, 4),
(32, 1),
(32, 4),
(33, 1),
(33, 4),
(34, 1),
(34, 4),
(35, 1),
(35, 4),
(36, 1),
(36, 4),
(37, 1),
(37, 4),
(38, 1),
(38, 4),
(39, 1),
(39, 4),
(40, 1),
(40, 4),
(41, 1),
(41, 4),
(42, 1),
(42, 4),
(43, 1),
(43, 4),
(44, 1),
(44, 4),
(45, 1),
(45, 4),
(46, 1),
(46, 4),
(47, 1),
(47, 4),
(48, 1),
(48, 4),
(49, 1),
(49, 4),
(49, 5),
(50, 1),
(50, 4),
(50, 5),
(51, 1),
(51, 4),
(52, 1),
(52, 4),
(53, 1),
(53, 4),
(53, 5),
(54, 1),
(54, 5),
(54, 10),
(55, 1),
(55, 5),
(55, 10),
(56, 1),
(56, 5),
(56, 10),
(57, 1),
(57, 5),
(57, 10),
(58, 1),
(58, 5),
(58, 10),
(59, 1),
(59, 5),
(59, 10),
(60, 1),
(60, 5),
(60, 10),
(61, 1),
(61, 5),
(61, 10),
(62, 1),
(62, 5),
(62, 10),
(63, 1),
(63, 5),
(64, 1),
(64, 4),
(65, 1),
(65, 4),
(66, 1),
(66, 4),
(67, 1),
(67, 4),
(68, 1),
(68, 4),
(69, 1),
(69, 4),
(70, 1),
(70, 4),
(71, 1),
(71, 4),
(72, 1),
(72, 4),
(73, 1),
(73, 4),
(74, 1),
(74, 4),
(75, 1),
(75, 4),
(76, 1),
(76, 4),
(77, 1),
(77, 4),
(78, 1),
(78, 4),
(79, 1),
(79, 4),
(80, 1),
(80, 4),
(81, 1),
(81, 4),
(82, 1),
(82, 4),
(83, 1),
(83, 4),
(84, 1),
(84, 4),
(85, 1),
(85, 4),
(86, 1),
(86, 4),
(87, 1),
(87, 4),
(88, 1),
(88, 4),
(89, 2),
(89, 9),
(90, 2),
(90, 9),
(91, 2),
(91, 9),
(92, 1),
(92, 2),
(92, 9),
(93, 1),
(93, 2),
(93, 9),
(94, 1),
(94, 2),
(94, 9),
(95, 1),
(95, 2),
(95, 9),
(96, 1),
(96, 2),
(96, 9),
(97, 1),
(97, 2),
(97, 9),
(98, 2),
(98, 9),
(98, 13),
(99, 1),
(99, 7),
(100, 1),
(100, 12),
(101, 1),
(101, 4),
(102, 1),
(102, 4),
(103, 1),
(103, 4),
(104, 1),
(104, 4),
(105, 1),
(105, 4),
(106, 1),
(106, 2),
(106, 4),
(106, 9),
(107, 1),
(107, 4),
(108, 1),
(108, 2),
(108, 4),
(108, 9),
(108, 13),
(109, 1),
(109, 2),
(109, 4),
(109, 9),
(109, 13),
(110, 1),
(110, 4),
(111, 1),
(111, 4),
(112, 1),
(112, 4),
(112, 10),
(113, 1),
(113, 4),
(113, 10),
(114, 1),
(114, 4),
(115, 1),
(115, 4),
(116, 1),
(116, 4),
(117, 1),
(117, 4),
(117, 10),
(118, 1),
(118, 4),
(119, 1),
(120, 1),
(120, 4),
(121, 1),
(121, 4),
(122, 1),
(122, 2),
(122, 4),
(122, 5),
(122, 7),
(122, 10),
(122, 11),
(122, 13),
(123, 1),
(123, 4),
(124, 1),
(124, 2),
(124, 4),
(124, 5),
(124, 10),
(125, 1),
(125, 4),
(126, 1),
(126, 2),
(126, 4),
(126, 5),
(126, 10),
(127, 1),
(128, 1),
(128, 4),
(129, 1),
(129, 4),
(130, 1),
(130, 2),
(130, 4),
(130, 5),
(130, 9),
(130, 10),
(130, 13),
(131, 1),
(131, 4),
(132, 1),
(132, 4),
(133, 1),
(133, 4),
(134, 1),
(134, 4),
(135, 1),
(135, 4),
(136, 1),
(136, 2),
(136, 4),
(136, 5),
(136, 10),
(136, 11),
(137, 1),
(138, 1),
(138, 4),
(139, 1),
(139, 4),
(140, 1),
(140, 6),
(141, 1),
(141, 4),
(142, 1),
(142, 4),
(143, 1),
(143, 4),
(144, 1),
(145, 1),
(145, 4),
(146, 1),
(146, 2),
(146, 4),
(146, 5),
(146, 10),
(147, 1),
(147, 2),
(147, 4),
(147, 5),
(147, 10),
(147, 11),
(148, 1),
(148, 4),
(149, 1),
(149, 4),
(150, 1),
(150, 2),
(150, 4),
(150, 5),
(150, 10);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `juego_desarrollador`
--

CREATE TABLE `juego_desarrollador` (
  `id_juego` int(11) NOT NULL,
  `id_desarrollador` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `juego_desarrollador`
--

INSERT INTO `juego_desarrollador` (`id_juego`, `id_desarrollador`) VALUES
(1, 1),
(2, 3),
(3, 3),
(4, 2),
(5, 2),
(6, 5),
(7, 5),
(8, 4),
(9, 4),
(10, 2),
(11, 12),
(12, 11),
(13, 23),
(14, 13),
(15, 23),
(16, 2),
(17, 13),
(18, 4),
(19, 10),
(20, 4),
(21, 6),
(22, 6),
(23, 6),
(24, 6),
(25, 6),
(26, 6),
(27, 6),
(28, 6),
(29, 6),
(30, 6),
(31, 6),
(32, 6),
(33, 6),
(34, 6),
(35, 6),
(36, 6),
(37, 6),
(38, 6),
(39, 6),
(40, 6),
(41, 6),
(42, 6),
(43, 6),
(44, 9),
(45, 9),
(46, 9),
(47, 9),
(48, 9),
(49, 9),
(50, 9),
(51, 9),
(52, 9),
(53, 9),
(54, 9),
(55, 9),
(56, 9),
(57, 9),
(58, 9),
(59, 9),
(60, 9),
(61, 9),
(62, 9),
(63, 9),
(64, 8),
(65, 8),
(66, 8),
(67, 8),
(68, 8),
(69, 8),
(70, 8),
(71, 8),
(72, 8),
(73, 8),
(74, 8),
(75, 8),
(76, 8),
(77, 8),
(78, 8),
(79, 8),
(80, 8),
(81, 8),
(82, 8),
(83, 8),
(84, 8),
(85, 8),
(86, 8),
(87, 8),
(88, 8),
(89, 7),
(90, 7),
(91, 7),
(92, 7),
(93, 7),
(94, 7),
(95, 7),
(96, 7),
(97, 7),
(98, 7),
(99, 7),
(100, 100),
(101, 7),
(102, 7),
(103, 7),
(104, 7),
(105, 7),
(106, 7),
(107, 7),
(108, 7),
(109, 7),
(110, 7),
(111, 7),
(112, 7),
(113, 7),
(114, 7),
(115, 7),
(116, 7),
(117, 7),
(118, 7),
(119, 7),
(120, 18),
(121, 17),
(122, 13),
(123, 16),
(124, 13),
(125, 20),
(126, 13),
(127, 19),
(128, 24),
(129, 22),
(130, 21),
(131, 25),
(132, 20),
(133, 21),
(134, 11),
(135, 16),
(136, 15),
(137, 15),
(138, 25),
(139, 14),
(140, 21),
(141, 11),
(142, 18),
(143, 19),
(144, 23),
(145, 12),
(146, 22),
(147, 24),
(148, 25),
(149, 8),
(150, 9);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `juego_editor`
--

CREATE TABLE `juego_editor` (
  `id_juego` int(11) NOT NULL,
  `id_editor` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `juego_editor`
--

INSERT INTO `juego_editor` (`id_juego`, `id_editor`) VALUES
(1, 1),
(2, 3),
(3, 3),
(4, 2),
(5, 2),
(6, 5),
(7, 5),
(8, 4),
(9, 4),
(10, 2),
(11, 26),
(12, 25),
(13, 4),
(14, 15),
(15, 4),
(16, 2),
(17, 13),
(18, 4),
(19, 10),
(20, 4),
(21, 6),
(22, 6),
(23, 6),
(24, 6),
(25, 6),
(26, 6),
(27, 6),
(28, 6),
(29, 6),
(30, 6),
(31, 6),
(32, 6),
(33, 6),
(34, 6),
(35, 6),
(36, 6),
(37, 6),
(38, 6),
(39, 6),
(40, 6),
(41, 6),
(42, 6),
(43, 6),
(44, 9),
(45, 9),
(46, 9),
(47, 9),
(48, 9),
(49, 9),
(50, 9),
(51, 9),
(52, 9),
(53, 9),
(54, 9),
(55, 9),
(56, 9),
(57, 9),
(58, 9),
(59, 9),
(60, 9),
(61, 9),
(62, 9),
(63, 9),
(64, 8),
(65, 8),
(66, 8),
(67, 8),
(68, 8),
(69, 8),
(70, 8),
(71, 8),
(72, 8),
(73, 8),
(74, 8),
(75, 8),
(76, 8),
(77, 8),
(78, 8),
(79, 8),
(80, 8),
(81, 8),
(82, 8),
(83, 8),
(84, 8),
(85, 8),
(86, 8),
(87, 8),
(88, 8),
(89, 7),
(90, 7),
(91, 7),
(92, 7),
(93, 7),
(94, 7),
(95, 7),
(96, 7),
(97, 7),
(98, 7),
(99, 7),
(100, 100),
(101, 7),
(102, 7),
(103, 7),
(104, 7),
(105, 7),
(106, 7),
(107, 7),
(108, 7),
(109, 7),
(110, 7),
(111, 7),
(112, 7),
(113, 7),
(114, 7),
(115, 7),
(116, 7),
(117, 7),
(118, 7),
(119, 7),
(120, 11),
(121, 12),
(122, 13),
(123, 14),
(124, 15),
(125, 16),
(126, 17),
(127, 18),
(128, 19),
(129, 20),
(130, 21),
(131, 22),
(132, 23),
(133, 24),
(134, 25),
(135, 26),
(136, 27),
(137, 28),
(138, 29),
(139, 30),
(140, 31),
(141, 32),
(142, 33),
(143, 34),
(144, 35),
(145, 36),
(146, 37),
(147, 38),
(148, 39),
(149, 40),
(150, 41);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `juego_etiqueta`
--

CREATE TABLE `juego_etiqueta` (
  `id_juego` int(11) NOT NULL,
  `id_etiqueta` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `juego_etiqueta`
--

INSERT INTO `juego_etiqueta` (`id_juego`, `id_etiqueta`) VALUES
(1, 1),
(1, 4),
(2, 2),
(2, 5),
(2, 11),
(3, 2),
(3, 5),
(3, 17),
(3, 18),
(4, 16),
(4, 22),
(4, 23),
(5, 5),
(5, 10),
(5, 16),
(6, 2),
(6, 22),
(7, 2),
(7, 5),
(8, 3),
(8, 15),
(8, 19),
(9, 3),
(9, 4),
(10, 1),
(10, 9),
(10, 10),
(11, 6),
(11, 21),
(12, 13),
(12, 15),
(13, 2),
(13, 6),
(13, 17),
(14, 8),
(14, 14),
(14, 24),
(14, 25),
(15, 6),
(15, 20),
(16, 7),
(16, 16),
(17, 23),
(17, 25),
(18, 1),
(18, 4),
(19, 16),
(19, 20),
(20, 3),
(20, 19),
(21, 2),
(21, 5),
(22, 2),
(22, 5),
(23, 2),
(23, 5),
(24, 2),
(24, 5),
(25, 2),
(25, 5),
(26, 2),
(26, 5),
(26, 19),
(27, 2),
(27, 5),
(28, 2),
(28, 5),
(29, 2),
(29, 5),
(30, 2),
(30, 5),
(31, 2),
(31, 5),
(32, 2),
(32, 5),
(33, 2),
(33, 5),
(34, 2),
(34, 5),
(35, 2),
(35, 5),
(36, 2),
(36, 5),
(37, 2),
(37, 5),
(38, 2),
(38, 5),
(39, 2),
(39, 5),
(39, 14),
(40, 2),
(40, 5),
(41, 2),
(41, 5),
(41, 10),
(42, 2),
(42, 5),
(43, 2),
(43, 5),
(44, 5),
(44, 9),
(44, 21),
(45, 5),
(45, 9),
(45, 21),
(46, 5),
(46, 9),
(46, 21),
(47, 5),
(47, 9),
(47, 21),
(48, 5),
(48, 9),
(48, 21),
(49, 5),
(49, 9),
(49, 21),
(50, 5),
(50, 9),
(50, 21),
(51, 5),
(51, 21),
(52, 5),
(52, 21),
(53, 5),
(53, 21),
(54, 6),
(54, 13),
(55, 6),
(55, 13),
(56, 6),
(56, 13),
(57, 6),
(57, 13),
(58, 6),
(58, 13),
(59, 6),
(59, 13),
(60, 6),
(60, 13),
(61, 6),
(61, 13),
(62, 6),
(62, 13),
(63, 3),
(63, 5),
(64, 18),
(64, 24),
(65, 5),
(65, 18),
(65, 24),
(66, 5),
(66, 18),
(66, 24),
(67, 5),
(67, 13),
(67, 18),
(67, 24),
(68, 5),
(68, 13),
(68, 18),
(68, 24),
(69, 5),
(69, 13),
(69, 18),
(69, 24),
(70, 5),
(70, 11),
(70, 13),
(70, 18),
(71, 5),
(71, 13),
(71, 18),
(72, 5),
(72, 13),
(72, 18),
(73, 5),
(73, 13),
(73, 18),
(74, 5),
(74, 13),
(74, 18),
(75, 5),
(75, 13),
(75, 18),
(76, 5),
(76, 13),
(76, 18),
(77, 5),
(77, 11),
(77, 13),
(77, 18),
(78, 5),
(78, 13),
(78, 17),
(78, 18),
(79, 3),
(79, 18),
(79, 24),
(80, 3),
(80, 18),
(80, 24),
(81, 3),
(81, 18),
(81, 24),
(82, 3),
(82, 5),
(82, 18),
(82, 24),
(83, 3),
(83, 5),
(83, 18),
(83, 24),
(84, 3),
(84, 5),
(84, 18),
(84, 24),
(85, 3),
(85, 5),
(85, 18),
(86, 3),
(86, 5),
(86, 18),
(87, 3),
(87, 5),
(87, 18),
(88, 3),
(88, 5),
(88, 18),
(89, 1),
(89, 4),
(90, 1),
(90, 4),
(91, 1),
(91, 4),
(91, 16),
(92, 1),
(92, 4),
(92, 23),
(93, 1),
(93, 4),
(93, 23),
(94, 1),
(94, 4),
(94, 23),
(95, 1),
(95, 4),
(96, 1),
(96, 4),
(96, 23),
(97, 1),
(97, 4),
(97, 23),
(98, 1),
(98, 4),
(98, 10),
(99, 4),
(99, 13),
(100, 12),
(100, 16),
(101, 13),
(102, 2),
(102, 13),
(103, 2),
(103, 13),
(104, 13),
(105, 2),
(105, 13),
(106, 2),
(106, 13),
(107, 2),
(107, 13),
(108, 2),
(108, 13),
(109, 2),
(109, 13),
(110, 5),
(110, 12),
(110, 16),
(111, 5),
(111, 12),
(111, 16),
(112, 5),
(112, 12),
(112, 16),
(113, 5),
(113, 12),
(113, 16),
(114, 5),
(114, 12),
(114, 16),
(115, 5),
(115, 12),
(115, 16),
(116, 5),
(116, 12),
(116, 16),
(117, 5),
(117, 12),
(117, 16),
(118, 5),
(118, 12),
(118, 16),
(119, 12),
(119, 16),
(120, 14),
(120, 22),
(121, 5),
(121, 12),
(121, 16),
(121, 21),
(122, 23),
(122, 25),
(123, 2),
(123, 8),
(124, 12),
(124, 14),
(124, 24),
(125, 5),
(125, 21),
(126, 2),
(126, 14),
(126, 24),
(127, 8),
(127, 14),
(128, 5),
(128, 13),
(128, 22),
(129, 5),
(129, 13),
(129, 15),
(130, 12),
(130, 13),
(130, 16),
(131, 2),
(131, 5),
(132, 2),
(132, 10),
(133, 5),
(133, 10),
(133, 16),
(134, 12),
(134, 16),
(134, 22),
(135, 21),
(136, 23),
(136, 25),
(137, 3),
(137, 14),
(137, 22),
(138, 3),
(138, 14),
(138, 20),
(139, 6),
(139, 22),
(139, 24),
(140, 7),
(140, 16),
(140, 22),
(141, 5),
(141, 6),
(141, 21),
(142, 6),
(142, 20),
(143, 11),
(143, 14),
(143, 16),
(144, 6),
(144, 13),
(144, 24),
(145, 16),
(145, 21),
(145, 24),
(146, 9),
(146, 10),
(147, 16),
(147, 22),
(148, 3),
(148, 5),
(148, 21),
(149, 3),
(149, 8),
(149, 25),
(150, 6),
(150, 17),
(150, 20);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `juego_genero`
--

CREATE TABLE `juego_genero` (
  `id_juego` int(11) NOT NULL,
  `id_genero` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `juego_genero`
--

INSERT INTO `juego_genero` (`id_juego`, `id_genero`) VALUES
(1, 1),
(2, 2),
(2, 3),
(3, 2),
(3, 4),
(4, 10),
(4, 11),
(5, 1),
(5, 3),
(6, 3),
(6, 13),
(7, 3),
(7, 4),
(8, 3),
(8, 17),
(9, 5),
(10, 1),
(10, 6),
(10, 18),
(11, 4),
(11, 16),
(12, 3),
(12, 14),
(13, 2),
(13, 3),
(14, 2),
(14, 8),
(15, 3),
(15, 15),
(16, 1),
(16, 4),
(17, 8),
(17, 11),
(18, 5),
(19, 1),
(19, 2),
(20, 2),
(21, 3),
(21, 4),
(21, 15),
(22, 3),
(22, 4),
(22, 15),
(23, 3),
(23, 4),
(23, 15),
(24, 3),
(24, 4),
(24, 15),
(25, 3),
(25, 4),
(25, 15),
(26, 3),
(26, 4),
(26, 15),
(27, 3),
(27, 4),
(27, 15),
(28, 3),
(28, 4),
(28, 15),
(29, 3),
(29, 4),
(29, 15),
(30, 3),
(30, 4),
(30, 15),
(31, 3),
(31, 4),
(31, 15),
(32, 3),
(32, 4),
(32, 15),
(33, 3),
(33, 4),
(33, 15),
(34, 1),
(34, 4),
(34, 18),
(35, 1),
(35, 4),
(35, 18),
(36, 1),
(36, 4),
(36, 18),
(37, 1),
(37, 4),
(37, 18),
(38, 1),
(38, 4),
(38, 18),
(39, 1),
(39, 4),
(39, 18),
(40, 1),
(40, 4),
(40, 18),
(41, 1),
(41, 4),
(41, 18),
(42, 1),
(42, 4),
(42, 18),
(43, 1),
(43, 4),
(43, 18),
(44, 3),
(44, 6),
(44, 18),
(45, 3),
(45, 6),
(45, 18),
(46, 3),
(46, 6),
(46, 18),
(47, 3),
(47, 6),
(47, 18),
(48, 3),
(48, 6),
(48, 18),
(49, 3),
(49, 6),
(49, 18),
(50, 3),
(50, 6),
(50, 18),
(51, 3),
(51, 6),
(51, 18),
(52, 3),
(52, 6),
(52, 18),
(53, 3),
(53, 6),
(53, 18),
(54, 2),
(54, 3),
(55, 2),
(55, 3),
(56, 2),
(56, 3),
(57, 2),
(57, 3),
(58, 2),
(58, 3),
(59, 2),
(59, 3),
(60, 2),
(60, 3),
(61, 2),
(61, 3),
(62, 2),
(62, 3),
(63, 2),
(63, 3),
(64, 2),
(64, 4),
(65, 2),
(65, 4),
(66, 2),
(66, 4),
(67, 2),
(67, 4),
(68, 2),
(68, 4),
(69, 2),
(69, 4),
(70, 2),
(70, 4),
(71, 2),
(71, 4),
(72, 2),
(72, 4),
(73, 2),
(73, 4),
(74, 2),
(74, 4),
(75, 2),
(75, 4),
(76, 2),
(76, 4),
(77, 2),
(77, 3),
(77, 4),
(78, 2),
(78, 3),
(78, 4),
(79, 2),
(79, 4),
(80, 2),
(80, 4),
(81, 2),
(81, 4),
(82, 2),
(82, 4),
(83, 2),
(83, 4),
(84, 2),
(84, 4),
(85, 2),
(85, 4),
(86, 2),
(86, 4),
(87, 2),
(87, 4),
(88, 2),
(88, 4),
(89, 1),
(89, 3),
(90, 1),
(90, 3),
(91, 1),
(91, 3),
(92, 1),
(92, 3),
(93, 1),
(93, 3),
(94, 1),
(94, 3),
(95, 1),
(95, 3),
(96, 1),
(96, 3),
(97, 1),
(97, 3),
(98, 1),
(98, 3),
(99, 7),
(100, 4),
(100, 13),
(101, 7),
(102, 7),
(103, 7),
(104, 7),
(105, 7),
(106, 7),
(107, 7),
(108, 7),
(109, 7),
(110, 1),
(110, 2),
(110, 3),
(111, 1),
(111, 2),
(111, 3),
(112, 1),
(112, 2),
(112, 3),
(113, 1),
(113, 2),
(113, 3),
(114, 1),
(114, 2),
(114, 3),
(115, 1),
(115, 3),
(115, 6),
(116, 1),
(116, 3),
(116, 6),
(117, 1),
(117, 3),
(117, 6),
(118, 1),
(118, 3),
(118, 6),
(119, 6),
(119, 11),
(120, 3),
(120, 8),
(120, 14),
(121, 4),
(122, 8),
(123, 4),
(123, 13),
(124, 4),
(124, 13),
(124, 18),
(125, 4),
(125, 15),
(126, 3),
(126, 13),
(126, 18),
(127, 8),
(127, 9),
(128, 3),
(128, 4),
(128, 5),
(129, 3),
(129, 4),
(130, 1),
(130, 3),
(131, 3),
(131, 4),
(131, 15),
(132, 2),
(132, 3),
(133, 1),
(133, 6),
(133, 18),
(134, 1),
(134, 2),
(135, 6),
(135, 15),
(136, 10),
(136, 11),
(137, 8),
(137, 9),
(138, 3),
(138, 8),
(138, 10),
(139, 3),
(139, 14),
(140, 4),
(140, 8),
(140, 11),
(141, 3),
(141, 4),
(142, 3),
(142, 5),
(142, 14),
(143, 2),
(143, 8),
(144, 1),
(144, 3),
(145, 6),
(145, 11),
(145, 18),
(146, 1),
(146, 3),
(146, 6),
(147, 1),
(147, 3),
(148, 4),
(148, 11),
(149, 2),
(149, 8),
(150, 2),
(150, 3);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `metodo_pago`
--

CREATE TABLE `metodo_pago` (
  `id_metodo` int(11) NOT NULL,
  `nombre_metodo` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `metodo_pago`
--

INSERT INTO `metodo_pago` (`id_metodo`, `nombre_metodo`) VALUES
(1, 'Tarjeta de Crédito'),
(2, 'PayPal'),
(3, 'Saldo Cartera');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `pago_compra`
--

CREATE TABLE `pago_compra` (
  `id_pago` int(11) NOT NULL,
  `id_compra` int(11) NOT NULL,
  `id_metodo` int(11) NOT NULL,
  `monto` decimal(10,2) NOT NULL,
  `id_tarjeta` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `pais`
--

CREATE TABLE `pais` (
  `id_pais` int(11) NOT NULL,
  `nombre_pais` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `pais`
--

INSERT INTO `pais` (`id_pais`, `nombre_pais`) VALUES
(3, 'Argentina'),
(5, 'Chile'),
(4, 'Colombia'),
(2, 'España'),
(1, 'México'),
(6, 'Perú'),
(7, 'Uruguay');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `reembolso`
--

CREATE TABLE `reembolso` (
  `id_reembolso` int(11) NOT NULL,
  `id_detalle` int(11) NOT NULL,
  `fecha_solicitud` date NOT NULL,
  `motivo` text DEFAULT NULL,
  `estado` varchar(20) DEFAULT 'Pendiente'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `tarjeta_bancaria`
--

CREATE TABLE `tarjeta_bancaria` (
  `id_tarjeta` int(11) NOT NULL,
  `id_usuario` int(11) NOT NULL,
  `numero_tarjeta` varchar(16) NOT NULL,
  `banco` varchar(50) NOT NULL,
  `titular` varchar(100) NOT NULL,
  `fecha_expiracion` varchar(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `tarjeta_bancaria`
--

INSERT INTO `tarjeta_bancaria` (`id_tarjeta`, `id_usuario`, `numero_tarjeta`, `banco`, `titular`, `fecha_expiracion`) VALUES
(1, 1, '4152000011112222', 'BBVA', 'Alejandro Villada', '12/28'),
(100, 100, '5555444433332222', 'Santander', 'Esteban Piloto', '11/27');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `usuario`
--

CREATE TABLE `usuario` (
  `id_usuario` int(11) NOT NULL,
  `nickname` varchar(50) NOT NULL,
  `email` varchar(100) NOT NULL,
  `password_hash` varchar(255) NOT NULL,
  `fecha_nacimiento` date NOT NULL,
  `saldo_cartera` decimal(10,2) DEFAULT 0.00,
  `id_pais` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `usuario`
--

INSERT INTO `usuario` (`id_usuario`, `nickname`, `email`, `password_hash`, `fecha_nacimiento`, `saldo_cartera`, `id_pais`) VALUES
(0, 'Pleble12', 'holaplebe@gmmail.com', 'holawe', '2000-01-01', 0.00, 1),
(1, 'Alejandro Villada', 'ale@mail.com', 'AlejandroVillada123', '1998-05-10', 100.00, 1),
(2, 'ShadowHunter', 'user2@mail.com', 'hash2', '1992-04-12', 15.50, 2),
(3, 'PixelQueen', 'user3@mail.com', 'hash3', '1998-11-05', 0.00, 3),
(4, 'CyberNinja', 'user4@mail.com', 'hash4', '2001-02-28', 50.00, 4),
(5, 'RetroKing', 'user5@mail.com', 'hash5', '1985-07-19', 120.00, 5),
(6, 'SniperPro', 'sniper@mail.com', 'h1', '2001-08-22', 15.00, 1),
(7, 'RPGfan', 'rpg@mail.com', 'h2', '1995-12-05', 120.00, 2),
(8, 'CasualGamer', 'casual@mail.com', 'h3', '1988-04-18', 0.00, 4),
(9, 'Speedrunner', 'speed@mail.com', 'h4', '2003-09-30', 45.50, 5),
(10, 'NoobMaster', 'noob@mail.com', 'h5', '2008-02-14', 10.00, 3),
(11, 'VR_Enthusiast', 'vr@mail.com', 'pwd1', '1990-07-12', 10.00, 6),
(12, 'FightingKing', 'fight@mail.com', 'pwd2', '2000-11-05', 100.00, 7),
(13, 'GhostRider', 'user13@mail.com', 'hash13', '1993-08-21', 10.00, 6),
(14, 'StarLord', 'user14@mail.com', 'hash14', '1990-01-15', 5.00, 7),
(15, 'NeonStriker', 'user15@mail.com', 'hash15', '2002-05-30', 25.00, 1),
(16, 'VoidWalker', 'user16@mail.com', 'hash16', '1997-12-11', 0.00, 2),
(17, 'CrimsonBlade', 'user17@mail.com', 'hash17', '1995-03-08', 60.00, 3),
(18, 'IronFist', 'user18@mail.com', 'hash18', '1988-09-22', 15.00, 4),
(19, 'SilverSurfer', 'user19@mail.com', 'hash19', '1999-04-17', 0.00, 5),
(20, 'DarkMage', 'user20@mail.com', 'hash20', '2003-10-05', 45.00, 6),
(21, 'LightBringer', 'user21@mail.com', 'hash21', '1994-06-25', 100.00, 7),
(22, 'StormChaser', 'user22@mail.com', 'hash22', '1991-11-13', 0.00, 1),
(23, 'FireCaster', 'user23@mail.com', 'hash23', '1989-02-14', 30.00, 2),
(24, 'IceQueen', 'user24@mail.com', 'hash24', '1996-08-09', 20.00, 3),
(25, 'EarthShaker', 'user25@mail.com', 'hash25', '2000-01-20', 0.00, 4),
(26, 'WindRider', 'user26@mail.com', 'hash26', '1992-05-16', 55.00, 5),
(27, 'ThunderGod', 'user27@mail.com', 'hash27', '1998-10-02', 15.00, 6),
(28, 'VenomStrike', 'user28@mail.com', 'hash28', '1995-07-28', 0.00, 7),
(29, 'BloodHound', 'user29@mail.com', 'hash29', '1990-12-04', 80.00, 1),
(30, 'SteelTitan', 'user30@mail.com', 'hash30', '1987-03-11', 0.00, 2),
(31, 'BronzeKnee', 'user31@mail.com', 'hash31', '2001-09-18', 25.00, 3),
(32, 'GoldenBoy', 'user32@mail.com', 'hash32', '1993-04-07', 40.00, 4),
(33, 'PlatinumG', 'user33@mail.com', 'hash33', '1996-11-22', 0.00, 5),
(34, 'DiamondDog', 'user34@mail.com', 'hash34', '1999-02-05', 15.00, 6),
(35, 'MasterChiefx', 'user35@mail.com', 'hash35', '1994-08-15', 60.00, 7),
(36, 'DoomSlayerx', 'user36@mail.com', 'hash36', '1991-05-09', 0.00, 1),
(37, 'VaultHunter', 'user37@mail.com', 'hash37', '2004-12-01', 35.00, 2),
(38, 'LoneWanderer', 'user38@mail.com', 'hash38', '1997-06-14', 0.00, 3),
(39, 'CourierSix', 'user39@mail.com', 'hash39', '1988-10-27', 20.00, 4),
(40, 'ChosenOne', 'user40@mail.com', 'hash40', '1992-01-19', 0.00, 5),
(41, 'Dragonborn', 'user41@mail.com', 'hash41', '1995-09-08', 75.00, 6),
(42, 'Nerevarine', 'user42@mail.com', 'hash42', '1990-03-23', 10.00, 7),
(43, 'HeroOfKvatch', 'user43@mail.com', 'hash43', '1986-07-12', 0.00, 1),
(44, 'ChampionAsh', 'user44@mail.com', 'hash44', '2002-11-30', 45.00, 2),
(45, 'RedTrainer', 'user45@mail.com', 'hash45', '1998-04-05', 0.00, 3),
(46, 'BlueRival', 'user46@mail.com', 'hash46', '1999-08-17', 25.00, 4),
(47, 'GreenLeaf', 'user47@mail.com', 'hash47', '2001-02-22', 0.00, 5),
(48, 'YellowSpark', 'user48@mail.com', 'hash48', '1994-10-09', 50.00, 6),
(49, 'CrystalClear', 'user49@mail.com', 'hash49', '1997-05-14', 0.00, 7),
(50, 'RubyRed', 'user50@mail.com', 'hash50', '1993-12-25', 15.00, 1),
(51, 'SapphireBlue', 'user51@mail.com', 'hash51', '1996-01-31', 30.00, 2),
(52, 'EmeraldGreen', 'user52@mail.com', 'hash52', '1990-06-18', 0.00, 3),
(53, 'FireRed', 'user53@mail.com', 'hash53', '2000-09-03', 40.00, 4),
(54, 'LeafGreen', 'user54@mail.com', 'hash54', '1989-04-21', 0.00, 5),
(55, 'HeartGold', 'user55@mail.com', 'hash55', '1995-11-08', 20.00, 6),
(56, 'SoulSilver', 'user56@mail.com', 'hash56', '1998-02-15', 0.00, 7),
(57, 'BlackKnight', 'user57@mail.com', 'hash57', '1992-07-29', 60.00, 1),
(58, 'WhiteWizard', 'user58@mail.com', 'hash58', '1987-10-10', 0.00, 2),
(59, 'SunBather', 'user59@mail.com', 'hash59', '2003-03-24', 15.00, 3),
(60, 'MoonWalker', 'user60@mail.com', 'hash60', '1991-08-06', 0.00, 4),
(61, 'UltraSun', 'user61@mail.com', 'hash61', '1994-12-19', 35.00, 5),
(62, 'UltraMoon', 'user62@mail.com', 'hash62', '1999-05-02', 0.00, 6),
(63, 'SwordMaster', 'user63@mail.com', 'hash63', '1996-09-14', 25.00, 7),
(64, 'ShieldBearer', 'user64@mail.com', 'hash64', '2001-01-27', 0.00, 1),
(65, 'ScarletFox', 'user65@mail.com', 'hash65', '1988-06-08', 45.00, 2),
(66, 'VioletSky', 'user66@mail.com', 'hash66', '1993-11-20', 0.00, 3),
(67, 'LinkAwakened', 'user67@mail.com', 'hash67', '1997-04-03', 10.00, 4),
(68, 'ZeldaPrincess', 'user68@mail.com', 'hash68', '1990-09-16', 0.00, 5),
(69, 'GanonBane', 'user69@mail.com', 'hash69', '1995-02-28', 55.00, 6),
(70, 'SamusAranx', 'user70@mail.com', 'hash70', '1989-07-11', 0.00, 7),
(71, 'RidleyBoss', 'user71@mail.com', 'hash71', '1992-12-24', 20.00, 1),
(72, 'MarioJump', 'user72@mail.com', 'hash72', '1985-05-07', 0.00, 2),
(73, 'LuigiGhost', 'user73@mail.com', 'hash73', '1998-10-19', 30.00, 3),
(74, 'BowserKing', 'user74@mail.com', 'hash74', '1994-03-04', 0.00, 4),
(75, 'PeachToad', 'user75@mail.com', 'hash75', '2000-08-16', 15.00, 5),
(76, 'YoshiEgg', 'user76@mail.com', 'hash76', '1991-01-29', 0.00, 6),
(77, 'WarioGold', 'user77@mail.com', 'hash77', '1987-06-12', 80.00, 7),
(78, 'WaluigiTime', 'user78@mail.com', 'hash78', '1996-11-25', 0.00, 1),
(79, 'SonicDash', 'user79@mail.com', 'hash79', '1993-04-08', 25.00, 2),
(80, 'TailsFly', 'user80@mail.com', 'hash80', '1999-09-21', 0.00, 3),
(81, 'KnucklesPunch', 'user81@mail.com', 'hash81', '1990-02-02', 40.00, 4),
(82, 'ShadowEdge', 'user82@mail.com', 'hash82', '2002-07-15', 0.00, 5),
(83, 'EggmanRobot', 'user83@mail.com', 'hash83', '1986-12-28', 10.00, 6),
(84, 'CrashSpin', 'user84@mail.com', 'hash84', '1995-05-11', 0.00, 7),
(85, 'SpyroFlame', 'user85@mail.com', 'hash85', '1998-10-24', 35.00, 1),
(86, 'SolidSnake', 'user86@mail.com', 'hash86', '1989-03-09', 0.00, 2),
(87, 'LiquidSnake', 'user87@mail.com', 'hash87', '1991-08-22', 20.00, 3),
(88, 'BigBoss', 'user88@mail.com', 'hash88', '1985-01-04', 0.00, 4),
(89, 'OcelotRevolver', 'user89@mail.com', 'hash89', '1994-06-17', 50.00, 5),
(90, 'RaidenCyborg', 'user90@mail.com', 'hash90', '1997-11-30', 0.00, 6),
(91, 'DanteDevil', 'user91@mail.com', 'hash91', '1992-04-13', 15.00, 7),
(92, 'VergilStorm', 'user92@mail.com', 'hash92', '1990-09-26', 0.00, 1),
(93, 'NeroArm', 'user93@mail.com', 'hash93', '2000-02-08', 30.00, 2),
(94, 'KratosRage', 'user94@mail.com', 'hash94', '1988-07-21', 0.00, 3),
(95, 'AtreusBoy', 'user95@mail.com', 'hash95', '2003-12-03', 25.00, 4),
(96, 'AloySeeker', 'user96@mail.com', 'hash96', '1996-05-16', 0.00, 5),
(97, 'NathanDrake', 'user97@mail.com', 'hash97', '1993-10-29', 45.00, 6),
(98, 'JoelSurvivor', 'user98@mail.com', 'hash98', '1985-03-12', 0.00, 7),
(99, 'EllieGuitar', 'user99@mail.com', 'hash99', '1999-08-25', 10.00, 1),
(100, 'StarPilot', 'star@mail.com', 'secureHash99', '2000-05-15', 0.00, 1),
(101, 'Diego Vazquez', 'diego.vazquez@ejemplo.com', 'DiegoVazquez123', '2000-01-01', 0.00, 1),
(102, 'Victor Dominguez', 'victor.dominguez@ejemplo.com', 'VictorDominguez123', '2000-01-01', 0.00, 1),
(103, 'Andrea Romero', 'andrea.romero@ejemplo.com', 'AndreRomero123', '2000-01-01', 0.00, 1),
(104, 'Jesus Masias', 'jesus.masias@ejemplo.com', 'JesusMasias123', '2000-01-01', 0.00, 1),
(105, 'Diego Aguilar', 'diego.aguilar@ejemplo.com', 'DiegoAguilar123', '2000-01-01', 0.00, 1),
(106, 'messi', 'messi@gmail.com', 'messi', '2000-01-01', 0.00, 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `videojuego`
--

CREATE TABLE `videojuego` (
  `id_juego` int(11) NOT NULL,
  `titulo` varchar(150) NOT NULL,
  `descripcion` text DEFAULT NULL,
  `precio_base` decimal(10,2) NOT NULL,
  `fecha_lanzamiento` date DEFAULT NULL,
  `jugadores_activos` int(11) DEFAULT 1500,
  `id_clasificacion` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Volcado de datos para la tabla `videojuego`
--

INSERT INTO `videojuego` (`id_juego`, `titulo`, `descripcion`, `precio_base`, `fecha_lanzamiento`, `jugadores_activos`, `id_clasificacion`) VALUES
(1, 'Valorant', 'Shooter táctico 5v5', 0.00, '2020-06-02', 1507, 2),
(2, 'Cyberpunk 2077', 'RPG de mundo abierto en Night City', 1199.00, '2020-12-10', 1500, 3),
(3, 'The Witcher 3', 'Caza monstruos en un mundo de fantasía', 599.00, '2015-05-18', 1501, 3),
(4, 'Portal 2', 'Resuelve puzzles con portales', 113.99, '2011-04-18', 1501, 1),
(5, 'Half-Life 2', 'Aventura de ciencia ficción clásica', 113.99, '2004-11-16', 1503, 3),
(6, 'Grand Theft Auto V', 'Mundo abierto y crimen', 599.00, '2015-04-14', 1502, 3),
(7, 'Red Dead Redemption 2', 'Aventura en el salvaje oeste', 1399.00, '2019-11-05', 1500, 3),
(8, 'One Piece Pirate Warriors 4', 'Juego de acción musou de piratas', 599.00, '2020-03-27', 1501, 2),
(9, 'Dragon Ball FighterZ', 'Juego de peleas 2.5D', 1199.00, '2018-01-26', 1500, 2),
(10, 'Left 4 Dead 2', 'Shooter cooperativo de zombies', 113.99, '2009-11-17', 1500, 3),
(11, 'Hollow Knight', 'Aventura de acción e insectos', 149.99, '2017-02-24', 1501, 2),
(12, 'Hades', 'Rogue-like de acción divina', 279.99, '2020-09-17', 1501, 2),
(13, 'Elden Ring', 'Mundo abierto implacable', 1199.00, '2022-02-25', 1502, 3),
(14, 'Stardew Valley', 'Simulador de granja pacífico', 149.99, '2016-02-26', 1502, 1),
(15, 'Sekiro', 'Acción ninja de alta dificultad', 1399.00, '2019-03-22', 1502, 3),
(16, 'Half-Life: Alyx', 'Shooter en Realidad Virtual', 59.99, '2020-03-23', 1501, 3),
(17, 'Overcooked! 2', 'Caos culinario cooperativo', 279.99, '2018-08-07', 1501, 1),
(18, 'Tekken 8', 'Torneo del Rey del Puño de Hierro', 1499.00, '2024-01-26', 1501, 2),
(19, 'Warframe', 'Acción cooperativa con trajes biomecánicos', 0.00, '2013-03-25', 150004, 3),
(20, 'One Piece Odyssey', 'Aventura RPG con la tripulación', 1199.00, '2023-01-13', 5000, 2),
(21, 'Assassin\'s Creed', 'El inicio de la orden', 149.99, '2007-11-13', 1200, 3),
(22, 'Assassin\'s Creed II', 'La historia de Ezio', 149.99, '2009-11-17', 2500, 3),
(23, 'Assassin\'s Creed Brotherhood', 'Roma bajo el control templario', 149.99, '2010-11-16', 1500, 3),
(24, 'Assassin\'s Creed Revelations', 'El fin de la trilogía de Ezio', 149.99, '2011-11-15', 1100, 3),
(25, 'Assassin\'s Creed III', 'La revolución americana', 599.00, '2012-10-30', 1800, 3),
(26, 'Assassin\'s Creed IV Black Flag', 'Piratas en el Caribe', 599.00, '2013-10-29', 4000, 3),
(27, 'Assassin\'s Creed Rogue', 'La perspectiva templaria', 279.99, '2014-11-11', 901, 3),
(28, 'Assassin\'s Creed Unity', 'Revolución francesa en cooperativo', 279.99, '2014-11-11', 2201, 3),
(29, 'Assassin\'s Creed Syndicate', 'Revolución industrial en Londres', 599.00, '2015-10-23', 1600, 3),
(30, 'Assassin\'s Creed Origins', 'El origen de la hermandad', 1199.00, '2017-10-27', 3500, 3),
(31, 'Assassin\'s Creed Odyssey', 'Mercenarios en la antigua Grecia', 1199.00, '2018-10-05', 4500, 3),
(32, 'Assassin\'s Creed Valhalla', 'Invasión vikinga en Inglaterra', 1199.00, '2020-11-10', 8000, 3),
(33, 'Assassin\'s Creed Mirage', 'Regreso a las raíces', 1399.00, '2023-10-05', 12000, 3),
(34, 'Far Cry', 'Supervivencia tropical', 113.99, '2004-03-23', 500, 3),
(35, 'Far Cry 2', 'Conflicto en África', 113.99, '2008-10-21', 600, 3),
(36, 'Far Cry 3', 'La locura en una isla', 149.99, '2012-11-29', 3000, 3),
(37, 'Far Cry 3: Blood Dragon', 'Expansión retro-futurista', 279.99, '2013-05-01', 1200, 3),
(38, 'Far Cry 4', 'Rebelión en el Himalaya', 279.99, '2014-11-18', 2100, 3),
(39, 'Far Cry Primal', 'Supervivencia en la edad de piedra', 279.99, '2016-02-23', 1500, 3),
(40, 'Far Cry 5', 'Secta religiosa en Montana', 1199.00, '2018-03-27', 4200, 3),
(41, 'Far Cry New Dawn', 'Secuela post-apocalíptica directa', 599.00, '2019-02-15', 1800, 3),
(42, 'Far Cry 6', 'Revolución en Yara', 1199.00, '2021-10-07', 6001, 3),
(43, 'Far Cry 6: Lost Between Worlds', 'Expansión dimensional', 19.99, '2022-12-06', 801, 3),
(44, 'Resident Evil HD', 'El horror original remasterizado', 149.99, '2015-01-20', 1500, 3),
(45, 'Resident Evil 2 Remake', 'Sobrevive a Raccoon City', 599.00, '2019-01-25', 5500, 3),
(46, 'Resident Evil 3 Remake', 'Escapa de Nemesis', 599.00, '2020-04-03', 3200, 3),
(47, 'Resident Evil 4', 'La misión de Leon en España', 149.99, '2005-01-11', 2800, 3),
(48, 'Resident Evil 4 Remake', 'Reimaginación del clásico moderno', 1399.00, '2023-03-24', 18000, 3),
(49, 'Resident Evil 5', 'Acción cooperativa en África', 149.99, '2009-03-05', 1800, 3),
(50, 'Resident Evil 6', 'Campaña global de terror', 279.99, '2012-10-02', 1200, 3),
(51, 'Resident Evil 7', 'Regreso al terror en primera persona', 149.99, '2017-01-24', 4000, 3),
(52, 'Resident Evil Village', 'Hombres lobo y vampiros', 599.00, '2021-05-07', 6500, 3),
(53, 'Resident Evil Revelations', 'Horror en un crucero', 279.99, '2012-01-26', 900, 3),
(54, 'Monster Hunter', 'El inicio de la cacería', 113.99, '2004-03-11', 100, 2),
(55, 'Monster Hunter Freedom Unite', 'Expansión portátil', 149.99, '2008-03-27', 300, 2),
(56, 'Monster Hunter Tri', 'Cacería submarina', 149.99, '2009-08-01', 400, 2),
(57, 'Monster Hunter 4 Ultimate', 'Combate vertical', 279.99, '2014-10-11', 800, 2),
(58, 'Monster Hunter Generations', 'Celebración de la franquicia', 599.00, '2015-11-28', 1100, 2),
(59, 'Monster Hunter World', 'La revolución HD', 599.00, '2018-01-26', 15000, 2),
(60, 'Monster Hunter World: Iceborne', 'Expansión maestro', 599.00, '2019-09-06', 12000, 2),
(61, 'Monster Hunter Rise', 'Acción rápida', 599.00, '2021-03-26', 18000, 2),
(62, 'Monster Hunter Rise: Sunbreak', 'Expansión occidental', 599.00, '2022-06-30', 14000, 2),
(63, 'Monster Hunter Stories 2', 'RPG por turnos', 1199.00, '2021-07-09', 2000, 2),
(64, 'Final Fantasy I', 'El primer cristal', 113.99, '1987-12-18', 500, 2),
(65, 'Final Fantasy II', 'Rebelión contra el imperio', 113.99, '1988-12-17', 400, 2),
(66, 'Final Fantasy III', 'Guerreros de la luz', 149.99, '1990-04-27', 450, 2),
(67, 'Final Fantasy IV', 'La redención de Cecil', 149.99, '1991-07-19', 800, 2),
(68, 'Final Fantasy V', 'El sistema de trabajos', 149.99, '1992-12-06', 750, 2),
(69, 'Final Fantasy VI', 'Magia y tecnología', 149.99, '1994-04-02', 1500, 2),
(70, 'Final Fantasy VII', 'El legendario Cloud', 149.99, '1997-01-31', 4000, 2),
(71, 'Final Fantasy VIII', 'SeeD y brujas', 149.99, '1999-02-11', 1800, 2),
(72, 'Final Fantasy IX', 'Retorno a la fantasía clásica', 599.00, '2000-07-07', 2200, 2),
(73, 'Final Fantasy X', 'El peregrinaje de Yuna', 599.00, '2001-07-19', 3000, 2),
(74, 'Final Fantasy XII', 'Intrigas políticas', 1199.00, '2006-03-16', 1500, 2),
(75, 'Final Fantasy XIII', 'Destino y fal\'Cie', 149.99, '2009-12-17', 900, 2),
(76, 'Final Fantasy XV', 'Viaje en coche', 599.00, '2016-11-29', 3500, 2),
(77, 'Final Fantasy VII Remake', 'Reconstrucción de Midgar', 1499.00, '2020-04-10', 8000, 2),
(78, 'Final Fantasy XVI', 'Acción oscura', 1499.00, '2023-06-22', 12000, 3),
(79, 'Dragon Quest I', 'El inicio del héroe', 113.99, '1986-05-27', 200, 1),
(80, 'Dragon Quest II', 'Los herederos de Erdrick', 113.99, '1987-01-26', 150, 1),
(81, 'Dragon Quest III', 'Semillas de la salvación', 149.99, '1988-02-10', 500, 1),
(82, 'Dragon Quest IV', 'Capítulos de los elegidos', 149.99, '1990-02-11', 400, 1),
(83, 'Dragon Quest V', 'La mano de la novia', 149.99, '1992-09-27', 600, 1),
(84, 'Dragon Quest VI', 'Los reinos oníricos', 149.99, '1995-12-09', 351, 1),
(85, 'Dragon Quest VII', 'Fragmentos del pasado', 599.00, '2000-08-26', 800, 1),
(86, 'Dragon Quest VIII', 'El periplo del Rey Maldito', 149.99, '2004-11-27', 1200, 2),
(87, 'Dragon Quest IX', 'Centinelas del firmamento', 599.00, '2009-07-11', 900, 2),
(88, 'Dragon Quest XI', 'Ecos de un pasado perdido', 599.00, '2017-07-29', 4500, 2),
(89, 'Battlefield 1942', 'Guerra clásica en PC', 113.99, '2002-09-10', 101, 3),
(90, 'Battlefield 2', 'Guerra moderna táctica', 113.99, '2005-06-21', 200, 3),
(91, 'Battlefield 2142', 'Guerra futurista', 113.99, '2006-10-17', 150, 3),
(92, 'Battlefield Bad Company 2', 'Destrucción total', 149.99, '2010-03-02', 800, 3),
(93, 'Battlefield 3', 'Guerra total', 149.99, '2011-10-25', 1500, 3),
(94, 'Battlefield 4', 'Guerra masiva', 149.99, '2013-10-29', 4000, 3),
(95, 'Battlefield Hardline', 'Policías contra ladrones', 149.99, '2015-03-17', 300, 3),
(96, 'Battlefield 1', 'Primera Guerra Mundial', 149.99, '2016-10-21', 6000, 3),
(97, 'Battlefield V', 'Segunda Guerra Mundial', 599.00, '2018-11-20', 5000, 3),
(98, 'Battlefield 2042', 'Guerra futurista a gran escala', 1199.00, '2021-11-19', 8500, 3),
(99, 'Need for Speed Underground', 'Tuning nocturno', 113.99, '2003-11-17', 500, 2),
(100, 'Galactic Frontier', 'Exploración y disparos en el espacio profundo', 1199.00, '2023-11-25', 1, 2),
(101, 'Need for Speed Underground 2', 'Mundo abierto', 113.99, '2004-11-09', 1200, 2),
(102, 'Need for Speed Most Wanted', 'Escapa de la policía', 113.99, '2005-11-15', 2000, 2),
(103, 'Need for Speed Carbon', 'Carreras en cañones', 113.99, '2006-10-31', 800, 2),
(104, 'Need for Speed ProStreet', 'Circuitos legales', 113.99, '2007-11-14', 301, 2),
(105, 'Need for Speed Hot Pursuit', 'Policía o corredor', 149.99, '2010-11-16', 1501, 2),
(106, 'Need for Speed Rivals', 'Conflicto en línea', 149.99, '2013-11-15', 600, 2),
(107, 'Need for Speed Payback', 'Acción y atracos', 599.00, '2017-11-10', 1100, 2),
(108, 'Need for Speed Heat', 'Día legal, noche ilegal', 1199.00, '2019-11-08', 3500, 2),
(109, 'Need for Speed Unbound', 'Estilo cel-shading', 1399.00, '2022-12-02', 4000, 2),
(110, 'Mass Effect', 'El viaje de Shepard', 149.99, '2007-11-20', 800, 3),
(111, 'Mass Effect 2', 'Misión suicida', 149.99, '2010-01-26', 2000, 3),
(112, 'Mass Effect 3', 'Guerra Reapers', 149.99, '2012-03-06', 1500, 3),
(113, 'Mass Effect Andromeda', 'Nueva galaxia', 599.00, '2017-03-21', 1100, 3),
(114, 'Mass Effect Legendary Edition', 'Trilogía remaster', 1199.00, '2021-05-14', 5000, 3),
(115, 'Dead Space', 'Terror en la Ishimura', 149.99, '2008-10-13', 1200, 3),
(116, 'Dead Space 2', 'La estación Sprawl', 149.99, '2011-01-25', 1500, 3),
(117, 'Dead Space 3', 'Terror en planeta helado', 149.99, '2013-02-05', 800, 3),
(118, 'Dead Space Remake', 'Clásico reconstruido', 1199.00, '2023-01-27', 6000, 3),
(119, 'Dead Space Ignition', 'Puzzles en conductos', 4.99, '2010-10-12', 50, 3),
(120, 'Cult of the Lamb', 'Administra tu propio culto', 279.99, '2022-08-11', 8500, 2),
(121, 'Outer Wilds', 'Exploración espacial en un bucle temporal', 279.99, '2019-05-28', 4200, 2),
(122, 'Overcooked! All You Can Eat', 'Caos en la cocina remasterizado', 599.00, '2021-03-23', 3000, 1),
(123, 'Sable', 'Viaje de descubrimiento en el desierto', 279.99, '2021-09-23', 800, 1),
(124, 'Starbound', 'Supervivencia sandbox intergaláctica', 14.99, '2016-07-22', 1500, 2),
(125, 'A Plague Tale: Innocence', 'Hermanos huyendo de la inquisición', 599.00, '2019-05-14', 2100, 3),
(126, 'Terraria', 'Excava, pelea, explora, construye', 113.99, '2011-05-16', 45000, 2),
(127, 'Cities: Skylines', 'Construcción y gestión de ciudades', 279.99, '2015-03-10', 12000, 1),
(128, 'Yakuza 0', 'El origen del dragón de Dojima', 149.99, '2018-08-01', 8000, 3),
(129, 'God of War', 'Kratos en la mitología nórdica', 1199.00, '2022-01-14', 25000, 3),
(130, 'Halo Infinite', 'El retorno del Jefe Maestro', 1199.00, '2021-12-08', 35000, 2),
(131, 'Batman: Arkham Knight', 'Sé el caballero de la noche', 149.99, '2015-06-23', 6000, 3),
(132, 'Biomutant', 'Fábula de Kung-Fu post-apocalíptica', 599.00, '2021-05-25', 1200, 2),
(133, 'Metro Exodus', 'Huye de las ruinas de Moscú', 279.99, '2019-02-15', 3800, 3),
(134, 'The Outer Worlds', 'RPG de ciencia ficción y corporaciones', 279.99, '2020-10-23', 4100, 3),
(135, 'Hello Neighbor', 'Descubre qué oculta tu vecino', 279.99, '2017-12-08', 5000, 2),
(136, 'Human: Fall Flat', 'Puzzles basados en físicas divertidas', 149.99, '2016-07-22', 18000, 1),
(137, 'Idol Manager', 'La cara oscura de la industria idol', 149.99, '2021-07-27', 900, 2),
(138, 'Sakuna: Of Rice and Ruin', 'Acción y agricultura tradicional', 279.99, '2020-11-10', 1500, 2),
(139, 'The Binding of Isaac: Rebirth', 'Rogue-like con temática bíblica', 279.99, '2014-11-04', 22000, 3),
(140, 'Rick and Morty: Virtual Rick-ality', 'Caos en realidad virtual', 279.99, '2017-04-20', 600, 3),
(141, 'Tunic', 'Pequeño zorro, gran aventura', 279.99, '2022-03-16', 3200, 1),
(142, 'Sifu', 'Venganza y artes marciales', 599.00, '2022-02-08', 4500, 3),
(143, 'Citizen Sleeper', 'Sobrevive en una estación espacial en ruinas', 149.99, '2022-05-05', 1100, 2),
(144, 'ULTRAKILL', 'Shooter frenético inspirado en los 90s', 279.99, '2020-09-03', 9500, 3),
(145, 'Signalis', 'Survival horror retro de ciencia ficción', 149.99, '2022-10-27', 2800, 3),
(146, 'World War Z', 'Supervivencia cooperativa masiva', 279.99, '2019-04-16', 5500, 3),
(147, 'Earth Defense Force 5', 'Salva la tierra de insectos gigantes', 599.00, '2019-07-11', 1300, 3),
(148, 'Danganronpa: Trigger Happy Havoc', 'Misterios y asesinatos escolares', 149.99, '2016-02-18', 3000, 3),
(149, 'Story of Seasons', 'Comienza tu nueva vida en la granja', 599.00, '2020-07-14', 2100, 1),
(150, 'Nioh 2', 'Combate samurái masocore', 599.00, '2021-02-05', 7000, 3);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `biblioteca`
--
ALTER TABLE `biblioteca`
  ADD PRIMARY KEY (`id_biblioteca`),
  ADD KEY `id_usuario` (`id_usuario`),
  ADD KEY `id_juego` (`id_juego`),
  ADD KEY `id_detalle` (`id_detalle`);

--
-- Indices de la tabla `categoria`
--
ALTER TABLE `categoria`
  ADD PRIMARY KEY (`id_categoria`);

--
-- Indices de la tabla `clasificacion_edad`
--
ALTER TABLE `clasificacion_edad`
  ADD PRIMARY KEY (`id_clasificacion`);

--
-- Indices de la tabla `compra`
--
ALTER TABLE `compra`
  ADD PRIMARY KEY (`id_compra`),
  ADD KEY `id_usuario` (`id_usuario`);

--
-- Indices de la tabla `desarrollador`
--
ALTER TABLE `desarrollador`
  ADD PRIMARY KEY (`id_desarrollador`);

--
-- Indices de la tabla `detalle_compra`
--
ALTER TABLE `detalle_compra`
  ADD PRIMARY KEY (`id_detalle`),
  ADD KEY `id_compra` (`id_compra`),
  ADD KEY `id_juego` (`id_juego`),
  ADD KEY `id_usuario_destino` (`id_usuario_destino`);

--
-- Indices de la tabla `editor`
--
ALTER TABLE `editor`
  ADD PRIMARY KEY (`id_editor`);

--
-- Indices de la tabla `etiqueta`
--
ALTER TABLE `etiqueta`
  ADD PRIMARY KEY (`id_etiqueta`);

--
-- Indices de la tabla `genero`
--
ALTER TABLE `genero`
  ADD PRIMARY KEY (`id_genero`);

--
-- Indices de la tabla `juego_categoria`
--
ALTER TABLE `juego_categoria`
  ADD PRIMARY KEY (`id_juego`,`id_categoria`),
  ADD KEY `id_categoria` (`id_categoria`);

--
-- Indices de la tabla `juego_desarrollador`
--
ALTER TABLE `juego_desarrollador`
  ADD PRIMARY KEY (`id_juego`,`id_desarrollador`),
  ADD KEY `id_desarrollador` (`id_desarrollador`);

--
-- Indices de la tabla `juego_editor`
--
ALTER TABLE `juego_editor`
  ADD PRIMARY KEY (`id_juego`,`id_editor`),
  ADD KEY `id_editor` (`id_editor`);

--
-- Indices de la tabla `juego_etiqueta`
--
ALTER TABLE `juego_etiqueta`
  ADD PRIMARY KEY (`id_juego`,`id_etiqueta`),
  ADD KEY `id_etiqueta` (`id_etiqueta`);

--
-- Indices de la tabla `juego_genero`
--
ALTER TABLE `juego_genero`
  ADD PRIMARY KEY (`id_juego`,`id_genero`),
  ADD KEY `id_genero` (`id_genero`);

--
-- Indices de la tabla `metodo_pago`
--
ALTER TABLE `metodo_pago`
  ADD PRIMARY KEY (`id_metodo`);

--
-- Indices de la tabla `pago_compra`
--
ALTER TABLE `pago_compra`
  ADD PRIMARY KEY (`id_pago`),
  ADD KEY `id_compra` (`id_compra`),
  ADD KEY `id_metodo` (`id_metodo`),
  ADD KEY `id_tarjeta` (`id_tarjeta`);

--
-- Indices de la tabla `pais`
--
ALTER TABLE `pais`
  ADD PRIMARY KEY (`id_pais`),
  ADD UNIQUE KEY `nombre_pais` (`nombre_pais`);

--
-- Indices de la tabla `reembolso`
--
ALTER TABLE `reembolso`
  ADD PRIMARY KEY (`id_reembolso`),
  ADD UNIQUE KEY `id_detalle` (`id_detalle`);

--
-- Indices de la tabla `tarjeta_bancaria`
--
ALTER TABLE `tarjeta_bancaria`
  ADD PRIMARY KEY (`id_tarjeta`),
  ADD KEY `id_usuario` (`id_usuario`);

--
-- Indices de la tabla `usuario`
--
ALTER TABLE `usuario`
  ADD PRIMARY KEY (`id_usuario`),
  ADD UNIQUE KEY `nickname` (`nickname`),
  ADD UNIQUE KEY `email` (`email`),
  ADD KEY `id_pais` (`id_pais`);

--
-- Indices de la tabla `videojuego`
--
ALTER TABLE `videojuego`
  ADD PRIMARY KEY (`id_juego`),
  ADD KEY `id_clasificacion` (`id_clasificacion`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `biblioteca`
--
ALTER TABLE `biblioteca`
  MODIFY `id_biblioteca` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=24;

--
-- AUTO_INCREMENT de la tabla `compra`
--
ALTER TABLE `compra`
  MODIFY `id_compra` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18;

--
-- AUTO_INCREMENT de la tabla `detalle_compra`
--
ALTER TABLE `detalle_compra`
  MODIFY `id_detalle` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=27;

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `biblioteca`
--
ALTER TABLE `biblioteca`
  ADD CONSTRAINT `biblioteca_ibfk_1` FOREIGN KEY (`id_usuario`) REFERENCES `usuario` (`id_usuario`),
  ADD CONSTRAINT `biblioteca_ibfk_2` FOREIGN KEY (`id_juego`) REFERENCES `videojuego` (`id_juego`),
  ADD CONSTRAINT `biblioteca_ibfk_3` FOREIGN KEY (`id_detalle`) REFERENCES `detalle_compra` (`id_detalle`);

--
-- Filtros para la tabla `compra`
--
ALTER TABLE `compra`
  ADD CONSTRAINT `compra_ibfk_1` FOREIGN KEY (`id_usuario`) REFERENCES `usuario` (`id_usuario`);

--
-- Filtros para la tabla `detalle_compra`
--
ALTER TABLE `detalle_compra`
  ADD CONSTRAINT `detalle_compra_ibfk_1` FOREIGN KEY (`id_compra`) REFERENCES `compra` (`id_compra`),
  ADD CONSTRAINT `detalle_compra_ibfk_2` FOREIGN KEY (`id_juego`) REFERENCES `videojuego` (`id_juego`),
  ADD CONSTRAINT `detalle_compra_ibfk_3` FOREIGN KEY (`id_usuario_destino`) REFERENCES `usuario` (`id_usuario`);

--
-- Filtros para la tabla `juego_categoria`
--
ALTER TABLE `juego_categoria`
  ADD CONSTRAINT `juego_categoria_ibfk_1` FOREIGN KEY (`id_juego`) REFERENCES `videojuego` (`id_juego`),
  ADD CONSTRAINT `juego_categoria_ibfk_2` FOREIGN KEY (`id_categoria`) REFERENCES `categoria` (`id_categoria`);

--
-- Filtros para la tabla `juego_desarrollador`
--
ALTER TABLE `juego_desarrollador`
  ADD CONSTRAINT `juego_desarrollador_ibfk_1` FOREIGN KEY (`id_juego`) REFERENCES `videojuego` (`id_juego`),
  ADD CONSTRAINT `juego_desarrollador_ibfk_2` FOREIGN KEY (`id_desarrollador`) REFERENCES `desarrollador` (`id_desarrollador`);

--
-- Filtros para la tabla `juego_editor`
--
ALTER TABLE `juego_editor`
  ADD CONSTRAINT `juego_editor_ibfk_1` FOREIGN KEY (`id_juego`) REFERENCES `videojuego` (`id_juego`),
  ADD CONSTRAINT `juego_editor_ibfk_2` FOREIGN KEY (`id_editor`) REFERENCES `editor` (`id_editor`);

--
-- Filtros para la tabla `juego_etiqueta`
--
ALTER TABLE `juego_etiqueta`
  ADD CONSTRAINT `juego_etiqueta_ibfk_1` FOREIGN KEY (`id_juego`) REFERENCES `videojuego` (`id_juego`),
  ADD CONSTRAINT `juego_etiqueta_ibfk_2` FOREIGN KEY (`id_etiqueta`) REFERENCES `etiqueta` (`id_etiqueta`);

--
-- Filtros para la tabla `juego_genero`
--
ALTER TABLE `juego_genero`
  ADD CONSTRAINT `juego_genero_ibfk_1` FOREIGN KEY (`id_juego`) REFERENCES `videojuego` (`id_juego`),
  ADD CONSTRAINT `juego_genero_ibfk_2` FOREIGN KEY (`id_genero`) REFERENCES `genero` (`id_genero`);

--
-- Filtros para la tabla `pago_compra`
--
ALTER TABLE `pago_compra`
  ADD CONSTRAINT `pago_compra_ibfk_1` FOREIGN KEY (`id_compra`) REFERENCES `compra` (`id_compra`),
  ADD CONSTRAINT `pago_compra_ibfk_2` FOREIGN KEY (`id_metodo`) REFERENCES `metodo_pago` (`id_metodo`),
  ADD CONSTRAINT `pago_compra_ibfk_3` FOREIGN KEY (`id_tarjeta`) REFERENCES `tarjeta_bancaria` (`id_tarjeta`);

--
-- Filtros para la tabla `reembolso`
--
ALTER TABLE `reembolso`
  ADD CONSTRAINT `reembolso_ibfk_1` FOREIGN KEY (`id_detalle`) REFERENCES `detalle_compra` (`id_detalle`);

--
-- Filtros para la tabla `tarjeta_bancaria`
--
ALTER TABLE `tarjeta_bancaria`
  ADD CONSTRAINT `tarjeta_bancaria_ibfk_1` FOREIGN KEY (`id_usuario`) REFERENCES `usuario` (`id_usuario`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
