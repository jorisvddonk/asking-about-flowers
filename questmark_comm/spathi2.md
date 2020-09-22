# QUESTMARK-OPTIONS-HEADER

    {
      "questmark-spec": "1.0",
      "initial-state": "Intro",
      "initial-context": {
        "SPATHI_MANNER": 0,
        "SPATHI_HOME_VISITS": 0,
        "KNOW_SPATHI_PASSWORD": 0,
        "FOUND_PLUTO_SPATHI": 1,
        "join_us_refusals": 0,


        "optionEnabled_what_doing_on_pluto_2": 0,
        "optionEnabled_what_doing_on_pluto_3": 0,
        "optionEnabled_what_about_ilwrath": 0,
        "optionEnabled_when_ilwrath": 0,
        "optionEnabled_what_about_moonbase": 0,
        "optionEnabled_what_about_other_spathi": 0,
        "optionEnabled_how_many_crew": 0,
        "optionEnabled_really_thousands": 0,
        "optionEnabled_full_of_monsters": 0,
        "optionEnabled_what_enemy": 0,
        "optionEnabled_why_you_here": 0,
        "optionEnabled_what_about_other_races": 0,
        "optionEnabled_what_blaze_of_glory": 0,
        "optionEnabled_what_about_yourself": 0
      }
    }

# Intro

`"SPATHI_MANNER" getContext 2 eq jgz {`

HATE_YOU_FOREVER

`_hostile exit`

`}`

SORRY_ABOUT_THAT

* [identify](#SpathiMustGrovel_identify)
* [hi_there](#SpathiOnPluto)

ARE_YOU_SURE

* [dont_kill](#SpathiOnPluto)

OK_WONT

* [we_fight_1](#ExitConversation)

```comment
  if (PLAYER_SAID(Response, tell_me_coordinates))
    NPCPhrase(FAKE_COORDINATES);
```

OK_WE_FIGHT_AT_PLUTO

`_hostile exit`

# SpathiMustGrovel_identify

I_FWIFFO

* [do_cultural](#SpathiMustGrovel_do_cultural)
* [youre_forgiven](#SpathiOnPluto)

THANKS_FOR_FORGIVENESS

* [die_slugboy](#ExitConversation)

# SpathiMustGrovel_do_cultural

WEZZY_WEZZAH

* [begin_ritual](#SpathiMustGrovel_begin_ritual)
* [you_wont_die_yet](#SpathiOnPluto)

ETERNAL_GRATITUDE

* [we_fight_2](#ExitConversation)
  

# SpathiMustGrovel_begin_ritual

MUST_DO_RITUAL_AT_HOME

* [you_may_live](#SpathiOnPluto)

GEE_THANKS

* [pay_for_crimes](#ExitConversation)
* [what_are_coordinates](#SpathiMustGrovel_what_are_coordinates)

# SpathiMustGrovel_what_are_coordinates

COORDINATES_ARE

* [youve_got_me_all_wrong](#SpathiOnPluto)

SORRY_NO_COORDS

* [tell_me_coordinates](#ExitConversation)

# SpathiOnPluto

_

* `"what_doing_on_pluto_1" _optionEnabled` [what_doing_on_pluto_1](#SpathiOnPluto) `"what_doing_on_pluto_1" _disableOption`

ABOUT_20_YEARS_AGO

`"what_doing_on_pluto_2" _enableOption`

* `"what_doing_on_pluto_2" _optionEnabled` [what_doing_on_pluto_2](#SpathiOnPluto) `"what_doing_on_pluto_2" _disableOption`

WHEN_URQUAN_ARRIVED

`"what_doing_on_pluto_3" _enableOption`

* `"what_doing_on_pluto_3" _optionEnabled` [what_doing_on_pluto_3](#SpathiOnPluto) `"what_doing_on_pluto_3" _disableOption`

STATIONED_ON_EARTH_MOON

`"what_about_ilwrath" _enableOption`
`"what_about_moonbase" _enableOption`

* `"what_about_ilwrath" _optionEnabled` [what_about_ilwrath](#SpathiOnPluto) `"what_about_ilwrath" _disableOption`

ABOUT_ILWRATH

`"when_ilwrath" _enableOption`

* `"when_ilwrath" _optionEnabled` [when_ilwrath](#SpathiOnPluto) `"when_ilwrath" _disableOption`

THEN_ILWRATH

* `"what_about_moonbase" _optionEnabled` [what_about_moonbase](#SpathiOnPluto) `"what_about_moonbase" _disableOption`

SET_UP_BASE

`"what_about_other_spathi" _enableOption`

* `"what_about_other_spathi" _optionEnabled` [what_about_other_spathi](#SpathiOnPluto) `"what_about_other_spathi" _disableOption`

SPATHI_ARE

`"how_many_crew" _enableOption`
`"what_enemy" _enableOption`

* `"how_many_crew" _optionEnabled` [how_many_crew](#SpathiOnPluto) `"how_many_crew" _disableOption`

THOUSANDS

`"really_thousands" _enableOption`

* `"really_thousands" _optionEnabled` [really_thousands](#SpathiOnPluto) `"really_thousands" _disableOption`

JUST_ME

`"full_of_monsters" _enableOption`

* `"full_of_monsters" _optionEnabled` [full_of_monsters](#SpathiOnPluto) `"full_of_monsters" _disableOption`

HOW_TRUE

* `"what_enemy" _optionEnabled` [what_enemy](#SpathiOnPluto) `"what_enemy" _disableOption`

ENEMY_IS

`"why_you_here" _enableOption`

* `"why_you_here" _optionEnabled` [why_you_here](#SpathiOnPluto) `"why_you_here" _disableOption`

DREW_SHORT_STRAW

* `"where_are_urquan" _optionEnabled` [where_are_urquan](#SpathiOnPluto) `"where_are_urquan" _disableOption`

URQUAN_LEFT

`"what_about_other_races" _enableOption`

* `"what_about_other_races" _optionEnabled` [what_about_other_races](#SpathiOnPluto) `"what_about_other_races" _disableOption`

ABOUT_OTHER_RACES

`"what_blaze_of_glory" _enableOption`

* `"what_blaze_of_glory" _optionEnabled` [what_blaze_of_glory](#SpathiOnPluto) `"what_blaze_of_glory" _disableOption`

BLAZE_IS

`"what_about_yourself" _enableOption`

* `"what_about_yourself" _optionEnabled` [what_about_yourself](#SpathiOnPluto) `"what_about_yourself" _disableOption`

ABOUT_MYSELF

* `"full_of_monsters" _optionDisabled` [join_us](#ExitConversation)

```comment
    if (EscortFeasibilityStudy(SPATHI_SHIP) == 0)
      NPCPhrase(TOO_SCARY);
    else
    {
      NPCPhrase(WILL_JOIN);

      AlienTalkSegue((COUNT)~0);
      AddEscortShips(SPATHI_SHIP, 1);
      /* Make the Eluder escort captained by Fwiffo alone */
      SetEscortCrewComplement(SPATHI_SHIP, 1,
                              NAME_OFFSET + NUM_CAPTAINS_NAMES);
    }
```

WILL_JOIN

`"SPATHI" _getShip`

* `"full_of_monsters" _optionEnabled` [join_us](#SpathiOnPluto)

```comment
    if (join_us_refusals == 0)
    {
      NPCPhrase(WONT_JOIN_1);
      ++join_us_refusals;
    }
    else if (join_us_refusals == 1)
    {
      NPCPhrase(WONT_JOIN_2);
      ++join_us_refusals;
    }
    else
      NPCPhrase(WONT_JOIN_3);
```

`"join_us_refusals" getContext 2 eq jgz {`

WONT_JOIN_3

`}`

`"join_us_refusals" getContext 1 eq jgz {`

WONT_JOIN_2

`"join_us_refusals" getContext 1 + "join_us_refusals" setContext`

`}`

`"join_us_refusals" getContext 0 eq jgz {`

WONT_JOIN_1

`"join_us_refusals" getContext 1 + "join_us_refusals" setContext`

`}`


* [changed_mind](#ExitConversation)

OK_WE_FIGHT_AT_PLUTO

`_hostile exit`

# ExitConversation

`exit`