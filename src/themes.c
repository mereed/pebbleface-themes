/*
Copyright (C) 2015 Mark Reed

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "pebble.h"
	  
static const uint32_t WEATHER_ICONS[] = {
  RESOURCE_ID_CLEAR_DAY,
  RESOURCE_ID_CLEAR_NIGHT,
  RESOURCE_ID_WINDY,
  RESOURCE_ID_COLD,
  RESOURCE_ID_PARTLY_CLOUDY_DAY,
  RESOURCE_ID_PARTLY_CLOUDY_NIGHT,
  RESOURCE_ID_HAZE,
  RESOURCE_ID_CLOUD,
  RESOURCE_ID_RAIN,
  RESOURCE_ID_SNOW,
  RESOURCE_ID_HAIL,
  RESOURCE_ID_CLOUDY,
  RESOURCE_ID_STORM,
  RESOURCE_ID_FOG,
  RESOURCE_ID_NA,
};

enum key {
  ICON_KEY = 0x0,
  BLUETOOTHVIBE_KEY = 0x1,
  HOURLYVIBE_KEY = 0x2,
  TEMP_KEY = 0x3,
  CONDITION_KEY = 0x4,
  BACKGROUND_KEY = 0x5
};

static AppSync sync;
static uint8_t sync_buffer[128];

static int background;
static int bluetoothvibe;
static int hourlyvibe;

static bool appStarted = false;

static uint8_t batteryPercent;

static GBitmap *battery_image = NULL;
static BitmapLayer *battery_image_layer;
static BitmapLayer *battery_layer;

Window *window;
static Layer *window_layer;

GBitmap *background_image = NULL;
static BitmapLayer *background_layer;

BitmapLayer *icon_layer;
GBitmap *icon_bitmap = NULL;

TextLayer *layer_date_text;
TextLayer *layer_date_text2;
TextLayer *layer_time_text;
TextLayer *layer_time_text2;

TextLayer *temp_layer;
TextLayer *condition_layer;

static GFont time_font;
//static GFont date_font;
static GFont temp_font;

int cur_day = -1;

int charge_percent = 0;

static int s_random = 7;
static int temp_random;


void theme_choice() {

	switch(background) {
		
		case 0: // nature
		
		if(s_random == 7){
			s_random = 0;
		} else {

			temp_random = rand() % 7;

			while(temp_random == s_random){
			    temp_random = rand() % 7;
		    }

		    s_random = temp_random;

	    if (background_image) {
		gbitmap_destroy(background_image);
		background_image = NULL;
    }

		   if(s_random == 0){
				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG6);
         } else if(s_random == 1){
				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG5);
         } else if(s_random == 2){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG7);
         } else if(s_random == 3){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG9);
         } else if(s_random == 4){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG10);
         } else if(s_random == 5){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG30);
         } else if(s_random == 6){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG34);
         } 
			
			/*else if(s_random == 7){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG35);
         }
		 */

	   if (background_image != NULL) {
		bitmap_layer_set_bitmap(background_layer, background_image);
		layer_set_hidden(bitmap_layer_get_layer(background_layer), false);
		layer_mark_dirty(bitmap_layer_get_layer(background_layer));
	   }
}

	    break;
		
		case 1: // space
		
		if(s_random == 7){
			s_random = 0;
		} else {

			temp_random = rand() % 7;

			while(temp_random == s_random){
			    temp_random = rand() % 7;
		    }

		    s_random = temp_random;

	    if (background_image) {
		gbitmap_destroy(background_image);
		background_image = NULL;
    }

		   if(s_random == 0){
				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG1);
         } else if(s_random == 1){
				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG28);
         } else if(s_random == 2){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG20);
         } else if(s_random == 3){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG26);
         } else if(s_random == 4){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG27);
         } else if(s_random == 5){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG31);
         } 	else if(s_random == 6){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG36);
         } 
			
			/* else if(s_random == 7){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG37);

         }*/
					
	   if (background_image != NULL) {
		bitmap_layer_set_bitmap(background_layer, background_image);
		layer_set_hidden(bitmap_layer_get_layer(background_layer), false);
		layer_mark_dirty(bitmap_layer_get_layer(background_layer));
    }
}	
		
	    break;

		case 2:  // abstract
		if(s_random == 7){
			s_random = 0;
		} else {

			temp_random = rand() % 7;

			while(temp_random == s_random){
			    temp_random = rand() % 7;
		    }

		    s_random = temp_random;

	    if (background_image) {
		gbitmap_destroy(background_image);
		background_image = NULL;
    }

		   if(s_random == 0){
			   background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG12);
         } else if(s_random == 1){
				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG14);
         } else if(s_random == 2){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG15);
         } else if(s_random == 3){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG16);
         } else if(s_random == 4){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG17);
         } else if(s_random == 5){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG24);
         } else if(s_random == 6){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG39);
         } 
			/* 
			} else if(s_random == 7){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG38);
				*/
			
	   if (background_image != NULL) {
		bitmap_layer_set_bitmap(background_layer, background_image);
		layer_set_hidden(bitmap_layer_get_layer(background_layer), false);
		layer_mark_dirty(bitmap_layer_get_layer(background_layer));
       }
	}				
	    break;
		
		case 3:  // shapes
		if(s_random == 7){
			s_random = 0;
		} else {

			temp_random = rand() % 7;

			while(temp_random == s_random){
			    temp_random = rand() % 7;
		    }

		    s_random = temp_random;

	    if (background_image) {
		gbitmap_destroy(background_image);
		background_image = NULL;
    }

		   if(s_random == 0){
			   background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG2);
         } else if(s_random == 1){
				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG19);
         } else if(s_random == 2){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG22);
         } else if(s_random == 3){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG23);
         } else if(s_random == 4){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG32);
         } else if(s_random == 5){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG33);
         } else if(s_random == 6){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG40);
         } 
				/* 
			} else if(s_random == 7){
 				background_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG38);
				*/
			
	   if (background_image != NULL) {
		bitmap_layer_set_bitmap(background_layer, background_image);
		layer_set_hidden(bitmap_layer_get_layer(background_layer), false);
		layer_mark_dirty(bitmap_layer_get_layer(background_layer));
       }
	}				
	    break;
	}
}
	
void change_battery_icon(bool charging) {

if (battery_image) {
    gbitmap_destroy(battery_image);
    battery_image = NULL;
  }
	if(charging) {
    battery_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY_CHARGE);
  }  else {
    battery_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT);
  }  
  bitmap_layer_set_bitmap(battery_image_layer, battery_image);
  layer_mark_dirty(bitmap_layer_get_layer(battery_image_layer));
}

static void sync_tuple_changed_callback(const uint32_t key, const Tuple* new_tuple, const Tuple* old_tuple, void* context) {
	if(new_tuple==NULL || new_tuple->value==NULL) {
		return;
	}
	
	switch (key) {
	  
	case CONDITION_KEY:
      text_layer_set_text(condition_layer, new_tuple->value->cstring);
    break;
	  
	case TEMP_KEY:
      text_layer_set_text(temp_layer, new_tuple->value->cstring);
      break;

	case ICON_KEY:
      if (icon_bitmap) {
        gbitmap_destroy(icon_bitmap);
      }
      icon_bitmap = gbitmap_create_with_resource(WEATHER_ICONS[new_tuple->value->uint8]);
      bitmap_layer_set_bitmap(icon_layer, icon_bitmap);
    break;
	  
    case BLUETOOTHVIBE_KEY:
      bluetoothvibe = new_tuple->value->uint8 != 0;
	  persist_write_bool(BLUETOOTHVIBE_KEY, bluetoothvibe);
    break;      
	  
    case HOURLYVIBE_KEY:
      hourlyvibe = new_tuple->value->uint8 != 0;
	  persist_write_bool(HOURLYVIBE_KEY, hourlyvibe);	  
    break;	  
	
	case BACKGROUND_KEY:
      background = new_tuple->value->uint8;
	  persist_write_bool(BACKGROUND_KEY, background);	  
	  theme_choice(); 
	break; 
	  
  }
}

void update_battery_state(BatteryChargeState charge_state) {

  batteryPercent = charge_state.charge_percent;

  if(batteryPercent==100) {
        change_battery_icon(false);
  
    return;
  }

  layer_set_hidden(bitmap_layer_get_layer(battery_layer), charge_state.is_charging);
  change_battery_icon(charge_state.is_charging);
 	
} 

void battery_layer_update_callback(Layer *me, GContext* ctx) {        
  //draw the remaining battery percentage
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(2, 2, ((batteryPercent/100.0)*10.0), 5), 0, GCornerNone);
}


static void toggle_bluetooth(bool connected) {

if (!connected) {
	  
        layer_set_hidden(text_layer_get_layer(temp_layer), true);
        layer_set_hidden(bitmap_layer_get_layer(icon_layer), true);
        layer_set_hidden(text_layer_get_layer(condition_layer), true);	
	
     } else {
	
       layer_set_hidden(text_layer_get_layer(temp_layer), false);
       layer_set_hidden(bitmap_layer_get_layer(icon_layer), false);
       layer_set_hidden(text_layer_get_layer(condition_layer), false);	
	
	}
	
	if (appStarted && bluetoothvibe) {
	  
    //vibe!
    vibes_short_pulse();
		
	}	
}

void bluetooth_connection_callback(bool connected) {
  toggle_bluetooth(connected);
}

void update_time(struct tm *tick_time) {

	static char time_text[] = "00:00";
    static char date_text[] = "xxx xxx 00xx xx xxx";

    char *time_format;

    int new_cur_day = tick_time->tm_year*1000 + tick_time->tm_yday;
    if (new_cur_day != cur_day) {
        cur_day = new_cur_day;

	switch(tick_time->tm_mday)
  {
    case 1 :
    case 21 :
    case 31 :
      strftime(date_text, sizeof(date_text), "%a, %est of %b", tick_time);
      break;
    case 2 :
    case 22 :
      strftime(date_text, sizeof(date_text), "%a, %end of %b", tick_time);
      break;
    case 3 :
    case 23 :
      strftime(date_text, sizeof(date_text), "%a, %erd of %b", tick_time);
      break;
    default :
      strftime(date_text, sizeof(date_text), "%a, %eth of %b", tick_time);
      break;
  }
	
	  text_layer_set_text(layer_date_text, date_text);
	  text_layer_set_text(layer_date_text2, date_text);
				
  }

    if (clock_is_24h_style()) {
        time_format = "%R";
		
    } else {
        time_format = "%l:%M";
    }

    strftime(time_text, sizeof(time_text), time_format, tick_time);

    if (!clock_is_24h_style() && (time_text[0] == '0')) {
        memmove(time_text, &time_text[1], sizeof(time_text) - 1);
    }

    text_layer_set_text(layer_time_text, time_text);
    text_layer_set_text(layer_time_text2, time_text);
}


void force_update(void) {
    toggle_bluetooth(bluetooth_connection_service_peek());
    time_t now = time(NULL);
    update_time(localtime(&now));
}

void hourvibe (struct tm *tick_time) {

  if(appStarted && hourlyvibe) {
    //vibe!
    vibes_short_pulse();
  }
}

void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
    update_time(tick_time);
	
if (units_changed & HOUR_UNIT) {	
	theme_choice();
    hourvibe(tick_time);
  }

// added this for testing
/*	
if (units_changed & MINUTE_UNIT) {
	theme_choice(); 
  }*/
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
	
  background_image = gbitmap_create_with_resource( RESOURCE_ID_IMAGE_BG6 );
  background_layer = bitmap_layer_create( layer_get_frame( window_layer ) );
  bitmap_layer_set_bitmap( background_layer, background_image );
  layer_add_child( window_layer, bitmap_layer_get_layer( background_layer ) );
	
	// resources

	time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_REGULAR_44));
  //  date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CUSTOM_16));
    temp_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CUSTOM_17));
	
    // layer position and alignment
	
#ifdef PBL_PLATFORM_CHALK
    layer_time_text = text_layer_create(GRect(0, 16, 180, 70));
    layer_time_text2 = text_layer_create(GRect(0, 18, 182, 70));
    layer_date_text = text_layer_create(GRect(0, 108, 180, 20));
    layer_date_text2 = text_layer_create(GRect(0, 109, 181, 20));

    temp_layer  = text_layer_create(GRect(0, 74, 54, 28));
    condition_layer  = text_layer_create(GRect(0, 74, 157, 40));
#else
	layer_time_text = text_layer_create(GRect(0, 10, 144, 70));
    layer_date_text = text_layer_create(GRect(0, 102, 144, 20));
	layer_time_text2 = text_layer_create(GRect(0, 11, 145, 70));
    layer_date_text2 = text_layer_create(GRect(0, 103, 145, 20));
	
    temp_layer  = text_layer_create(GRect(0, 68, 40, 28));
    condition_layer  = text_layer_create(GRect(0, 68, 135, 40));
#endif
	
    text_layer_set_background_color(layer_date_text, GColorClear);
    text_layer_set_font(layer_date_text, temp_font);
    text_layer_set_background_color(layer_time_text, GColorClear);
    text_layer_set_font(layer_time_text, time_font);
    text_layer_set_background_color(layer_date_text2, GColorClear);
    text_layer_set_font(layer_date_text2, temp_font);
    text_layer_set_background_color(layer_time_text2, GColorClear);
    text_layer_set_font(layer_time_text2, time_font);
	
	text_layer_set_background_color(temp_layer, GColorClear);
    text_layer_set_font(temp_layer, temp_font);
	text_layer_set_background_color(condition_layer, GColorClear);
    text_layer_set_font(condition_layer, temp_font);	

    text_layer_set_text_alignment(layer_date_text, GTextAlignmentCenter);
    text_layer_set_text_alignment(layer_time_text, GTextAlignmentCenter);
    text_layer_set_text_alignment(layer_date_text2, GTextAlignmentCenter);
    text_layer_set_text_alignment(layer_time_text2, GTextAlignmentCenter);
	
    text_layer_set_text_alignment(temp_layer, GTextAlignmentRight);
    text_layer_set_text_alignment(condition_layer, GTextAlignmentRight);

	// set-up layer colours
    text_layer_set_text_color(layer_time_text, GColorWhite);
    text_layer_set_text_color(layer_date_text, GColorWhite);
    text_layer_set_text_color(layer_time_text2, GColorBlack);
    text_layer_set_text_color(layer_date_text2, GColorBlack);

    text_layer_set_text_color(temp_layer, GColorBlack);
    text_layer_set_text_color(condition_layer, GColorBlack);
 

	// composing layers
    layer_add_child(window_layer, text_layer_get_layer(layer_date_text2));
    layer_add_child(window_layer, text_layer_get_layer(layer_time_text2));
    layer_add_child(window_layer, text_layer_get_layer(layer_date_text));
    layer_add_child(window_layer, text_layer_get_layer(layer_time_text));
	
    layer_add_child(window_layer, text_layer_get_layer(condition_layer));
	layer_add_child(window_layer, text_layer_get_layer(temp_layer));
	

#ifdef PBL_PLATFORM_CHALK
  icon_layer = bitmap_layer_create(GRect(75, 71, 28, 28));
#else
  icon_layer = bitmap_layer_create(GRect(57, 65, 28, 28));
#endif
  layer_add_child(window_layer, bitmap_layer_get_layer(icon_layer));


  battery_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATT);
  GRect bitmap_bounds_batt = gbitmap_get_bounds(battery_image);
#ifdef PBL_PLATFORM_CHALK
  GRect frame_batt = GRect(82, 4, bitmap_bounds_batt.size.w, bitmap_bounds_batt.size.h);
#else
  GRect frame_batt = GRect(67, 4, bitmap_bounds_batt.size.w, bitmap_bounds_batt.size.h);
#endif
  battery_layer = bitmap_layer_create(frame_batt);
  battery_image_layer = bitmap_layer_create(frame_batt);
  bitmap_layer_set_bitmap(battery_image_layer, battery_image);
  layer_set_update_proc(bitmap_layer_get_layer(battery_layer), battery_layer_update_callback);
  layer_add_child(window_layer, bitmap_layer_get_layer(battery_image_layer));
  layer_add_child(window_layer, bitmap_layer_get_layer(battery_layer));

    // handlers
    battery_state_service_subscribe(&update_battery_state);
    bluetooth_connection_service_subscribe(&toggle_bluetooth);
    tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);

    appStarted = true;
	
	// update the battery on launch
    update_battery_state(battery_state_service_peek());
	
    // draw first frame
    force_update();
	
}

static void window_unload(Window *window) {

  layer_remove_from_parent(bitmap_layer_get_layer(background_layer));
  bitmap_layer_destroy(background_layer);

	if (background_image != NULL) {
		gbitmap_destroy(background_image);
    }
	
  layer_remove_from_parent(bitmap_layer_get_layer(icon_layer));
  bitmap_layer_destroy(icon_layer);
  gbitmap_destroy(icon_bitmap);
  icon_bitmap = NULL;
	
  layer_remove_from_parent(bitmap_layer_get_layer(battery_layer));
  bitmap_layer_destroy(battery_layer);
  gbitmap_destroy(battery_image);
  battery_image = NULL;
  
  layer_remove_from_parent(bitmap_layer_get_layer(battery_image_layer));
  bitmap_layer_destroy(battery_image_layer);
	
  text_layer_destroy( layer_time_text );
  text_layer_destroy( layer_date_text );
  text_layer_destroy( layer_time_text2 );
  text_layer_destroy( layer_date_text2 );
  text_layer_destroy( temp_layer );
  text_layer_destroy( condition_layer );
	
  fonts_unload_custom_font(time_font);
//  fonts_unload_custom_font(date_font);
  fonts_unload_custom_font(temp_font);
	
  layer_remove_from_parent(window_layer);
  layer_destroy(window_layer);
	
}

void main_window_push() {
  window = window_create();
  window_set_background_color(window, GColorWhite);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);
}

static void init() {
  main_window_push();

   Tuplet initial_values[] = {
	TupletCString(CONDITION_KEY, ""),
	TupletCString(TEMP_KEY, ""),
    TupletInteger(ICON_KEY, (uint8_t) 14),
    TupletInteger(BLUETOOTHVIBE_KEY, persist_read_bool(BLUETOOTHVIBE_KEY)),
    TupletInteger(HOURLYVIBE_KEY, persist_read_bool(HOURLYVIBE_KEY)),
    TupletInteger(BACKGROUND_KEY, persist_read_bool(BACKGROUND_KEY)),	
  };
  
	app_message_open(128, 128);

	app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values, ARRAY_LENGTH(initial_values),
      sync_tuple_changed_callback, NULL, NULL);
   
  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
  battery_state_service_subscribe(&update_battery_state);
  bluetooth_connection_service_subscribe(&toggle_bluetooth);
	
}

void handle_deinit(void) {
	
  app_sync_deinit(&sync);

  tick_timer_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
  battery_state_service_unsubscribe();
	
  window_destroy(window);

}

int main(void) {
    init();
    app_event_loop();
    handle_deinit();
}
