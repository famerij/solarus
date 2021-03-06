/*
 * Copyright (C) 2006-2014 Christopho, Solarus - http://www.solarus-games.org
 * 
 * Solarus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Solarus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "entities/DynamicTile.h"
#include "entities/Tileset.h"
#include "entities/TilePattern.h"
#include "entities/Hero.h"
#include "lowlevel/FileTools.h"
#include "lowlevel/Debug.h"
#include "Game.h"
#include "Map.h"

namespace solarus {

/**
 * \brief Creates a new dynamic tile on the map.
 * \param name a name to identify this tile
 * \param layer layer of the tile
 * \param x x position of the tile on the map
 * \param y y position of the tile on the map
 * \param width width of the tile (the pattern can be repeated)
 * \param height height of the tile (the pattern can be repeated)
 * \param tileset The tileset to use.
 * \param tile_pattern_id id of the tile pattern in the tileset
 * \param enabled true to make the tile initially enabled.
 */
DynamicTile::DynamicTile(
    const std::string& name,
    Layer layer,
    int x,
    int y,
    int width,
    int height,
    Tileset& tileset,
    int tile_pattern_id,
    bool enabled):
  MapEntity(name, 0, layer, x, y, width, height),
  tile_pattern_id(tile_pattern_id),
  tile_pattern(tileset.get_tile_pattern(tile_pattern_id)) {

  set_enabled(enabled);
}

/**
 * \brief Destructor.
 */
DynamicTile::~DynamicTile() {

}

/**
 * \brief Returns the type of entity.
 * \return the type of entity
 */
EntityType DynamicTile::get_type() const {

  return ENTITY_DYNAMIC_TILE;
}

/**
 * \brief Returns whether entities of this type can override the ground
 * of where they are placed.
 * \return \c true if this type of entity can change the ground.
 */
bool DynamicTile::is_ground_modifier() const {
  return true;
}

/**
 * \brief When is_ground_modifier() is \c true, returns the ground defined
 * by this entity.
 * \return The ground defined by this entity.
 */
Ground DynamicTile::get_modified_ground() const {
  return tile_pattern.get_ground();
}

/**
 * \brief Draws the tile on the map.
 */
void DynamicTile::draw_on_map() {

  if (!is_drawn()) {
    return;
  }

  const Rectangle& camera_position = get_map().get_camera_position();
  Rectangle dst(0, 0);

  Rectangle dst_position(get_top_left_x() - camera_position.get_x(),
      get_top_left_y() - camera_position.get_y(),
      get_width(), get_height());

  tile_pattern.fill_surface(get_map().get_visible_surface(), dst_position,
      get_map().get_tileset(), camera_position);
}

}

