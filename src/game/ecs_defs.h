// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// Components list - must have at least one element
//
struct Transform;
struct Image;
struct FramedImage;
struct Miracle;
struct Immunity;
struct Health;
struct Mortal;

#define _CMPS_LIST_ \
	Transform, \
	Image, \
    FramedImage, \
    Miracle, \
    Immunity, \
    Health, \
    Mortal

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	GHOSTS, \
    FOOD, \
    HELPERS

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    PACMAN

// Systems list - must have at least one element
//
class RenderSystem;
class PacManSystem;
class CollisionsSystem;
class GhostSystem;
class FoodSystem;
class ImmunitySystem;
class HelperSystem;

#define _SYS_LIST_ \
	RenderSystem, \
	PacManSystem, \
	CollisionsSystem, \
    GhostSystem, \
    FoodSystem, \
    ImmunitySystem, \
    HelperSystem
