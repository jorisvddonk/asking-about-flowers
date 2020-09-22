# Intro

`"spathi-000.ogg" _playAudio`

Attention big, mean, hostile alien vessel hovering overhead in an obvious attack posture:
This is Spathi Captain Fwiffo.
I know you are going to torture me, so let's just get this over with right now.
The coordinates of my homeworld, Spathiwa, are 241.6, 368.7
and the ultra-secret Spathi Cypher, which is known only by me and several billion other Spathi
is 'Huffi-Muffi-Guffi'.
Sorry about that little mistake with your landing vehicle!
I was so startled when it approached my vessel in a threatening manner that
er
my automated defense systems fired on it when it got too close.
I hope nobody got hurt!

```comment
			/* if already know password from Melnorme,
			 * but haven't visited Spathiwa yet . . .
			 */
		if (GET_GAME_STATE (SPATHI_HOME_VISITS) == 7)
		{
			SET_GAME_STATE (KNOW_SPATHI_PASSWORD, 0);
			SET_GAME_STATE (SPATHI_HOME_VISITS, 0);
		}
```

* [Attention alien vessel: Identify yourself or be destroyed!](#SpathiMustGrovel_identify)
* [hi_there](#SpathiOnPluto_hi_there)
* [dont_kill](#SpathiOnPluto_dont_kill)
* [we_fight_1](#ExitConversation)

# SpathiMustGrovel_identify

`"spathi-001.ogg" _playAudio`

Of course, of course!
As I said, I am Captain Fwiffo of the Spathi voidship StarRunner.
Our sensors have tracked your entry into this system
which you are no doubt here to conquer
and while you are certainly welcome to do so we would be greatly appreciative
if you would please just go away and forget this star system ever existed.
If you don't go, it will greatly complicate our master-slave relationship with the Ur-Quan
who stationed us here to watch over the Earthlings.

* [do_cultural](#SpathiMustGrovel_do_cultural)
* [youre_forgiven](#SpathiOnPluto_youre_forgiven)
* [die_slugboy](#ExitConversation)

# SpathiMustGrovel_do_cultural

`"spathi-004.ogg" _playAudio`

Certainly, most gracious destroyer, as is well known, before departing this mortal helix
all Spathi must complete the short, poignant ritual of Wezzy-Wezzah to be assured of a secure afterlife
and by allowing us to fulfill this requirement, you too shall be granted immortality in our beautiful afterworld
which is absolutely guaranteed to be free of similarly immortal monsters who would otherwise eat the both of us.

* [begin_ritual](#SpathiMustGrovel_begin_ritual)
* [you_wont_die_yet](#SpathiOnPluto_you_wont_die_yet)
* [we_fight_2](#ExitConversation)

# SpathiMustGrovel_begin_ritual

`"spathi-005.ogg" _playAudio`

Grief and woe -- certainly a destroyer of innocents as well-travelled as yourself
must know that the formalities of Wezzy-Wezzah are invalid unless
performed on the large moon orbiting our homeworld, Spathiwa
which is only 143 light years distant, and, if I remember correctly,
is especially beautiful this time of year.
Shall we go now there?

* [you_may_live](#SpathiOnPluto_you_may_live)
* [pay_for_crimes](#ExitConversation)
* [what_are_coordinates](#SpathiMustGrovel_what_are_coordinates)

# SpathiMustGrovel_what_are_coordinates

`"spathi-009.ogg" _playAudio`
My most wonderful planet Spathiwa circles a safe distance from the orange giant star Yuffo
which is at HyperSpace coordinates
hey -- wait a minute!
Is this some kind of Homosap trick to get the location of my homeworld
so that you can visit it with devastation?!

* [youve_got_me_all_wrong](#SpathiOnPluto_youve_got_me_all_wrong)
* [Just tell me the coordinates, alien dog-slime!](#ExitConversation)


# ExitConversation

```comment
??
```

`exit`
