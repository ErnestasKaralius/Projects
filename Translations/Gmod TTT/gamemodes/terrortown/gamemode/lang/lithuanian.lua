---- Lithuanian language strings

local L = LANG.CreateLanguage("Lietuvių")

--- General text used in various places
L.traitor    = "Išdavikas"
L.detective  = "Detektyvas"
L.innocent   = "Nekaltas"
L.last_words = "Paskutiniai žodžiai"

L.terrorists = "Teroristai"
L.spectators = "Stebėtojai"

--- Round status messages
L.round_minplayers = "Nepakanka žaidėjų raundo pradėjimui..."
L.round_voting     = "Vyksta balsavimas, raundo pradžia atidėta {num} sek..."
L.round_begintime  = "Naujas raundas prasidės po {num} sek. Pasiruoškite."
L.round_selected   = "Išdavikai pasirinkti."
L.round_started    = "Raundas prasidėjo!"
L.round_restart    = "Raundą iš naujo pradėjo administratorius."

L.round_traitors_one  = "Išdavikė, dabar tu vienas."
L.round_traitors_more = "Išdavikė, tai yra tavo partneriai: {names}"

L.win_time         = "Laikas baigėsi. Išdavikai pralaimėjo."
L.win_traitor      = "Išdavikai laimėjo!"
L.win_innocent     = "Išdavikai nugalėti!"
L.win_showreport   = "Pažvelkime {num} sek. į raundo rezultatus."

L.limit_round      = "Pasiekta raundų riba. {mapname} netrukus įsikels."
L.limit_time       = "Pasiekta laiko riba. {mapname} netrukus įsikels."
L.limit_left       = "Liko {num} raundas (-ai/-ų) arba {time} min. iki žemėlapio pakeitimo į {mapname}."

--- Credit awards
L.credit_det_all   = "Detektyvai, už jūsų veiksmus buvote apdovanoti kreditais ({num})."
L.credit_tr_all    = "Išdavikai, už jūsų veiksmus buvote apdovanoti kreditais ({num})."

L.credit_kill      = "Gauta kreditų už žaidėjo vaidmenyje {role} nužudimą: {num}."

--- Karma
L.karma_dmg_full   = "Jūsų karma yra {amount}, todėl šiame raunde darysite pilną žalą!"
L.karma_dmg_other  = "Jūsų karma yra {amount}, todėl jūsų daroma žala sumažinta {num}%."

--- Body identification messages
L.body_found       = "{finder} rado {victim} kūną. {role}"

-- The {role} in body_found will be replaced by one of the following:
L.body_found_t     = "Jis buvo išdavikas!"
L.body_found_d     = "Jis buvo detektyvas."
L.body_found_i     = "Jis buvo nekaltas."

L.body_confirm     = "{finder} patvirtino {victim} mirtį."

L.body_call        = "{player} kviečia detektyvą prie {victim} kūno!"
L.body_call_error  = "Prieš kviesdami detektyvą, turite patvirtinti žaidėjo mirtį!"

L.body_burning     = "Ai! Šis kūnas dega!"
L.body_credits     = "Rasta kreditų ant kūno: {num}."

--- Menus and windows
L.close = "Uždaryti"
L.cancel = "Atšaukti"

-- For navigation buttons
L.next = "Toliau"
L.prev = "Atgal"

-- Equipment buying menu
L.equip_title     = "Įranga"
L.equip_tabtitle  = "Įrangos pirkimas"

L.equip_status    = "Užsakymo būsena"
L.equip_cost      = "Liko kreditų: {num}."
L.equip_help_cost = "Bet kokia įranga kainuoja 1 kreditą."

L.equip_help_carry = "Galite pirkti tik tuos daiktus, kuriems turite vietos."
L.equip_carry      = "Galite nusipirkti šį daiktą."
L.equip_carry_own  = "Jau turite šį daiktą."
L.equip_carry_slot = "Jau turite ginklą {slot}-oje inventoriaus vietoje."

L.equip_help_stock = "Kai kuriuos daiktus galima nusipirkti tik vieną kartą per raundą."
L.equip_stock_deny = "Šio daikto nėra sandėlyje."
L.equip_stock_ok   = "Šis daiktas yra sandėlyje."

L.equip_custom     = "Šį daiktą pridėjo serveris."

L.equip_spec_name  = "Pavadinimas"
L.equip_spec_type  = "Rūšis"
L.equip_spec_desc  = "Apibūdinimas"

L.equip_confirm    = "Pirkti"

-- Disguiser tab in equipment menu
L.disg_name      = "Maskuotė"
L.disg_menutitle = "Maskuotės valdymas"
L.disg_not_owned = "Neturite maskuotės!"
L.disg_enable    = "Įjungti maskuotę."

L.disg_help1     = "Kai maskuotė įjungta, jūsų vardas, sveikata ir karma nerodomi tiems, kurie į jus žiūri. Be to, jūs būsite paslėpti nuo detektyvo radaro."
L.disg_help2     = "Spustelėkite skaičių klaviatūros ENTER, kad įjungtumėte arba išjungtumėte maskuotę nenaudojant meniu. Taip pat galite priskirti kitą klavišą su „ttt_toggle_disguise“ naudojant konsolę."

-- Radar tab in equipment menu
L.radar_name      = "Radaras"
L.radar_menutitle = "Radaro valdymas"
L.radar_not_owned = "Neturite radaro!"
L.radar_scan      = "Paieška"
L.radar_auto      = "Automatiškai kartoti paiešką."
L.radar_help      = "Paieškos rezultatai bus rodomi po {num} sek., po to radaras iš naujo įsikraus ir galės vėl būti naudojamas."
L.radar_charging  = "Radaras vis dar įkraunamas!"

-- Transfer tab in equipment menu
L.xfer_name       = "Perdavimas"
L.xfer_menutitle  = "Kreditų perdavimas"
L.xfer_no_credits = "Neturite kreditų!"
L.xfer_send       = "Perduoti kreditą"
L.xfer_help       = "Galite perduoti kreditus tik žaidėjams vaidmenyje {role}."

L.xfer_no_recip   = "Kredito perdavimas atšauktas: negaliojantis gavėjas."
L.xfer_no_credits = "Nepakanka kreditų perdavimui."
L.xfer_success    = "Kreditų perdavimas {player} baigtas."
L.xfer_received   = "{player} perduoda jums {num} kreditą (-us/-ų)."

-- Radio tab in equipment menu
L.radio_name      = "Radijas"
L.radio_help      = "Norėdami groti pasirinktą garsą, spustelėkite mygtuką."
L.radio_notplaced = "Norėdami groti garsus, turite padėti radiją."

-- Radio soundboard buttons
L.radio_button_scream  = "Klyksmas"
L.radio_button_expl    = "Sprogimas"
L.radio_button_pistol  = "Pistoletas"
L.radio_button_m16     = "M16"
L.radio_button_deagle  = "Deagle"
L.radio_button_mac10   = "MAC10"
L.radio_button_shotgun = "Lygiavamzdis šautuvas"
L.radio_button_rifle   = "Graižtvinis šautuvas"
L.radio_button_huge    = "H.U.G.E."
L.radio_button_c4      = "C4 pypsėjimas"
L.radio_button_burn    = "Degimas"
L.radio_button_steps   = "Žingsniai"


-- Intro screen shown after joining
L.intro_help     = "Jei esate naujokas, spustelėkite F1, kad atidarytumėte instrukciją!"

-- Radiocommands/quickchat
L.quick_title   = "Spartieji pranešimai"

L.quick_yes     = "Taip."
L.quick_no      = "Ne."
L.quick_help    = "Pagalbos!"
L.quick_imwith  = "Aš su {player}."
L.quick_see     = "Aš matau {player}."
L.quick_suspect = "{player} elgiasi įtartinai."
L.quick_traitor = "{player} yra išdavikas!"
L.quick_inno    = "{player} yra nekaltas."
L.quick_check   = "Ar kas nors gyvas?"

-- {player} in the quickchat text normally becomes a player nickname, but can
-- also be one of the below.  Keep these lowercase.
L.quick_nobody    = "niekas"
L.quick_disg      = "kažkas užsimaskavęs"
L.quick_corpse    = "neatpažintas kūnas"
L.quick_corpse_id = "{player} kūnas"


--- Body search window
L.search_title  = "Kūno apžiūros rezultatai"
L.search_info   = "Informacija"
L.search_confirm = "Patvirtinti mirtį"
L.search_call   = "Kviesti detektyvą"

-- Descriptions of pieces of information found
L.search_nick   = "Tai yra {player} lavonas."

L.search_role_t = "Šis žmogus buvo išdavikas!"
L.search_role_d = "Šis žmogus buvo detektyvas."
L.search_role_i = "Šis žmogus buvo nekaltas."

L.search_words  = "Kažkas jums pasakinėja, kad jo paskutiniai žodžiai buvo: „{lastwords}“"
L.search_armor  = "Jis dėvėjo nestandartinę šarvinę liemenę."
L.search_disg   = "Jis nešiojo prietaisą, kuris galėjo nuslėpti jo tapatybę."
L.search_radar  = "Jis nešiojo kažkokį radarą, kuris jau nebeveikia."
L.search_c4     = "Kišenėje radote raštelį. Jame sakoma, kad galima saugiai išminuoti bombą perpjaunant {num}-ąjį laidą."

L.search_dmg_crush  = "Dauguma kaulų yra sulaužyti. Matyt, smūgis kažko sunkaus buvo mirties priežastis."
L.search_dmg_bullet = "Akivaizdu, kad jis buvo nušautas."
L.search_dmg_fall   = "Jis nukrito iki mirties."
L.search_dmg_boom   = "Patirti sužalojimai ir apdegę drabužiai rodo, kad sprogimas buvo mirties priežastis."
L.search_dmg_club   = "Visas kūnas apdaužytas ir mėlynėse. Aišku, kad jis buvo sumuštas iki mirties."
L.search_dmg_drown  = "Kūnas rodo aiškius nuskendimo požymius."
L.search_dmg_stab   = "Jis buvo nudurtas ir mirė nukraujavęs."
L.search_dmg_burn   = "Čia kvepia keptu teroristu..."
L.search_dmg_tele   = "Panašu, kad DNR buvo užšifruota tachniono spinduliuote!"
L.search_dmg_car    = "Kai šis teroristas pereidinėjo per kelią, jį partrenkė neatsargus vairuotojas."
L.search_dmg_other  = "Neįmanoma nustatyti šio teroristo konkrečios mirties priežasties."

L.search_weapon = "Panašu, kad nužudymui buvo naudojamas {weapon}."
L.search_head   = "Mirtinas sužalojimas buvo šūvis į galvą. Nebuvo laiko klykti."
L.search_time   = "Nuo jo mirties iki jūsų apžiūrėjimo praėjo maždaug {time}."
L.search_dna    = "Surinkite DNR mėginį iš žudiko su DNR skaitytuvo pagalba. DNR mėginys suirs maždaug po {time}."

L.search_kills1 = "Radote nužudymų sąrašą, patvirtinantį {player} mirtį."
L.search_kills2 = "Radote nužudymų sąrašą, patvirtinantį mirtis:"
L.search_eyes   = "Naudodamiesi savo detektyvo įgūdžiais supratote, kad paskutinis matytas asmuo buvo {player}. Žudikas ar tik sutapimas?"


-- Scoreboard
L.sb_playing    = "Žaidžiate..."
L.sb_mapchange  = "Žemėlapis pasikeis po {num} raundo (-ų) arba {time}"

L.sb_mia        = "Dingę"
L.sb_confirmed  = "Mirę"

L.sb_ping       = "Delsa"
L.sb_deaths     = "Mirtys"
L.sb_score      = "Taškai"
L.sb_karma      = "Karma"

L.sb_info_help  = "Apžiūrėkite šio žaidėjo kūną ir rezultatus galėsite peržiūrėti čia."

L.sb_tag_friend = "DRAUGAS"
L.sb_tag_susp   = "ĮTARIAMASIS"
L.sb_tag_avoid  = "VENGTI"
L.sb_tag_kill   = "NUŽUDYTI"
L.sb_tag_miss   = "DINGO"

--- Help and settings menu (F1)

L.help_title = "Pagalba ir nustatymai"

-- Tabs
L.help_tut     = "Instrukcija"
L.help_tut_tip = "Kaip žaisti TTT 6 žingsniais"

L.help_settings = "Nustatymai"
L.help_settings_tip = "Kliento nustatymai"

-- Settings
L.set_title_gui = "Sąsajos nustatymai"

L.set_tips      = "Rodyti patarimus stebėjimo metu ekrano apačioje."

L.set_startpopup = "Iššokančio lango trukmė raundo pradžioje"
L.set_startpopup_tip = "Kai prasideda raundas, kelioms sekundėms ekrano apačioje pasirodo nedidelis iššokantis langas. Čia galima pakeisti jo rodymo laiką."

L.set_cross_opacity   = "Kryžmės neskaidrumas nusitaikant"
L.set_cross_disable   = "Išjungti kryžmę."
L.set_minimal_id      = "Minimali informacija apie taikinį po kryžme (be teksto apie karmą, užuominas ir pan.)."
L.set_healthlabel     = "Rodyti sveikatos būseną sveikatos juostoje."
L.set_lowsights       = "Nuleisti ginklą nusitaikant."
L.set_lowsights_tip   = "Jei įjungsite šią funkciją, ginklo modelis nusileis nusitaikant. Jums bus lengviau matyti savo taikinį, bet atrodys ne taip tikroviška."
L.set_fastsw          = "Spartusis ginklų keitimas"
L.set_fastsw_tip      = "Įjunkite, jei norite keisti ginklus be patvirtinančio spustelėjimo."
L.set_fastsw_menu     = "Įjungti ginklų keitimo meniu su sparčiuoju ginklų keitimu."
L.set_fastswmenu_tip  = "Kai įjungtas spartusis ginklų keitimas, pasirodinės perjungimo meniu."
L.set_wswitch         = "Išjungti ginklų keitimo meniu automatinį uždarymą."
L.set_wswitch_tip     = "Keitimo meniu automatiškai užsidaro praėjus kelioms sekundėms po paskutinio slinkimo. Jei įjungsite šią funkciją, meniu neužsidarinės."
L.set_cues            = "Groti raundo pradžios ir pabaigos garsus."


L.set_title_play    = "Žaidimo nustatymai"

L.set_specmode      = "Stebėjimo režimas (visada būti stebėtoju)."
L.set_specmode_tip  = "Stebėjimo režimas neleis prisikelti raundo pradžioje, todėl būsite stebėtojas."
L.set_mute          = "Nutildyti gyvus žaidėjus po mirties."
L.set_mute_tip      = "Ši funkcija nutildys gyvus žaidėjus, kai esate mirę arba stebite raundą."


L.set_title_lang    = "Kalbos nustatymai"

-- It may be best to leave this next one english, so english players can always
-- find the language setting even if it's set to a language they don't know.
L.set_lang          = "Pasirinkite kalbą (Select language):"


--- Weapons and equipment, HUD and messages

-- Equipment actions, like buying and dropping
L.buy_no_stock    = "Šios prekės nėra sandėlyje: ją jau nusipirkote šiame raunde."
L.buy_pending     = "Jau turite užsakymą. Palaukite, kol jį gausite."
L.buy_received    = "Gavote savo specialią įrangą."

L.drop_no_room    = "Nėra vietos ginklų išmetimui!"

L.disg_turned_on  = "Maskuotė įjungta!"
L.disg_turned_off = "Maskuotė išjungta."

-- Equipment item descriptions
L.item_passive    = "Daiktas su pasyviu efektu"
L.item_active     = "Daiktas su aktyviu efektu"
L.item_weapon     = "Ginklas"

L.item_armor      = "Šarvinė liemenė"
L.item_armor_desc = [[
Sumažina kulkų žalą 30%.

Standartinė detektyvų įranga.]]

L.item_radar      = "Radaras"
L.item_radar_desc = [[
Leidžia rasti gyvus žmones.

Automatinė paieška prasidės iškart
po nusipirkimo. Nustatymai pasiekiami šio meniu
skirtuke „Radaras“.]]

L.item_disg       = "Maskuotė"
L.item_disg_desc  = [[
Slepia informaciją apie jus. Taip pat nebūsite rodomi
kaip paskutinis žmogus, kuris matė mirusįjį.

Įjungti ir išjungti maskuotę galima skirtuke
„Maskuotė“ arba spustelėjus skaičių klaviatūros ENTER.]]

-- C4
L.c4_hint         = "Spustelėkite {usekey}, kad užtaisytumėte/išminuotumėte."
L.c4_no_disarm    = "Negalite išminuoti kito išdaviko C4, kol jis dar gyvas."
L.c4_disarm_warn  = "Jūsų užtaisytas C4 buvo išminuotas."
L.c4_armed        = "Užtaisėte bombą."
L.c4_disarmed     = "Išminavote bombą."
L.c4_no_room      = "Negalite pasiimti C4."

L.c4_desc         = "Galinga bomba su laikmačiu."

L.c4_arm          = "Užtaisyti"
L.c4_arm_timer    = "Laikmatis"
L.c4_arm_seconds  = "Sekundžių iki sprogimo:"
L.c4_arm_attempts = "Bandant išminuoti, {num} iš 6 laidų sukelia sprogimą."

L.c4_remove_title    = "Šalinimas"
L.c4_remove_pickup   = "Pasiimti"
L.c4_remove_destroy1 = "Sunaikinti"
L.c4_remove_destroy2 = "Patvirtinti"

L.c4_disarm       = "Išminuoti"
L.c4_disarm_cut   = "Spustelėkite, kad perkirptumėte {num}-ąjį laidą."

L.c4_disarm_t     = "Perkirpkite laidą, kad išminuotumėte bombą. Išdavikams bet koks laidas yra saugus. Nekaltiems nėra taip lengva!"
L.c4_disarm_owned = "Perkirpkite laidą, kad išminuotumėte bombą. Tai jūsų bomba, todėl bet koks laidas yra saugus."
L.c4_disarm_other = "Perkirpkite saugų laidą, kad išminuotumėte bombą. Ji sprogs, jei suklysite!"

L.c4_status_armed    = "UŽTAISYTA"
L.c4_status_disarmed = "IŠMINUOTA"

-- Visualizer
L.vis_name        = "Vizualizatorius"
L.vis_hint        = "Spustelėkite {usekey}, kad pasiimtumėte. (tik detektyvams)."

L.vis_help_pri    = "{primaryfire}: išmesti įjungtą prietaisą."

L.vis_desc        = [[
Prietaisas, vizualizuojantis nusikaltimo vietą.

Analizuoja kūną, kad parodytų, kaip auka
buvo nužudyta, bet tik tuo atveju,
jei ji buvo nušauta.]]

-- Decoy
L.decoy_name      = "Masalas"
L.decoy_no_room   = "Negalite pasiimti šio masalo."
L.decoy_broken    = "Jūsų masalas sunaikintas!"

L.decoy_help_pri  = "{primaryfire}: padėti masalą."

L.decoy_desc      = [[
Detektyvų radaruose rodo netikrą žymę
ir priverčia DNR skaitytuvus rodyti jūsų
masalo vietą, jei jie ieško naudojant jūsų DNR.]]

-- Defuser
L.defuser_name    = "Išminavimo rinkinys"
L.defuser_help    = "{primaryfire}: išminuoti C4."

L.defuser_desc    = [[
Akimirksniu išminuoja C4.

Neribotas naudojimas. C4 bus galima lengviau
pastebėti, jei turite šį daiktą.]]

-- Flare gun
L.flare_name      = "Signalinis pistoletas"
L.flare_desc      = [[
Gali būti naudojamas kūnams padegti,
kad jų niekada nesurastų. Ribotas
šovinių skaičius.

Degantys kūnai skleidžia ypatingą garsą.]]

-- Health station
L.hstation_name   = "Gydymo stotelė"
L.hstation_hint   = "Spustelėkite {usekey}, kad atgautumėte sveikatos. Įkrova: {num}."
L.hstation_broken = "Jūsų gydymo stotelė sunaikinta!"
L.hstation_help   = "{primaryfire}: padėti gydymo stotelę."

L.hstation_desc   = [[
Leidžia žaidėjams atgauti sveikatos.

Lėta įkrova.
Bet kas gali ja naudotis ir sunaikinti. Taip pat galite
surinkti DNR mėginius iš žmonių, kurie ją panaudojo.]]

-- Knife
L.knife_name      = "Peilis"
L.knife_thrown    = "Išmestas peilis"

L.knife_desc      = [[
Akimirksniu ir tyliai nužudo sužeistus žmones,
bet gali būti panaudotas tik vieną kartą.

Galima mesti su papildomu puolimo klavišu.]]

-- Poltergeist
L.polter_desc     = [[
Ant daiktų uždeda greitintuvus
ir tada smarkiai stumia juos aplink.

Energijos sprogimai daro žalos
visiems netoliese esantiems žmonėms.]]

-- Radio
L.radio_broken    = "Jūsų radijas sunaikintas!"
L.radio_help_pri  = "{primaryfire}: padėti radiją."

L.radio_desc      = [[
Groja garsus. Gali būti panaudotas dėmesio
atitraukimui arba apgavimui.

Padėkite jį kažkur, tada šio meniu skirtuke
„Radijas“ pasirinkite norimą garsą. ]]

-- Silenced pistol
L.sipistol_name   = "Pistoletas su duslintuvu"

L.sipistol_desc   = [[
Tylus pistoletas, naudoja įprastus
pistoleto šovinius.

Aukos po mirties neklyks.]]

-- Newton launcher
L.newton_name     = "Niutono patranka"

L.newton_desc     = [[
Stumkite žmones iš saugaus atstumo.

Turi neribotus šovinius, bet lėtai šaudo.]]

-- Binoculars
L.binoc_name      = "Žiūronai"
L.binoc_desc      = [[
Žiūrėkite į kūną su žiūronais, kad jį
iš tolo atpažintumėte ir apžiūrėtumėte.

Neribotas naudojimas, bet kūno apžiūrėjimas
trunka šiek tiek laiko.]]

L.binoc_help_pri  = "{primaryfire}: apžiūrėti kūną."
L.binoc_help_sec  = "{secondaryfire}: keisti priartinimo lygį."

-- UMP
L.ump_desc        = [[
Eksperimentinis pistoletas-kulkosvaidis,
dezorientuojantis taikinius.

Naudoja įprastus pistoleto-kulkosvaidžio šovinius.]]

-- DNA scanner
L.dna_name        = "DNR skaitytuvas"
L.dna_identify    = "Norint surinkti žudiko DNR mėginį, kūnas turi būti atpažintas."
L.dna_notfound    = "Nerasta DNR mėginių."
L.dna_limit       = "Nepakanka vietos. Išmeskite senus mėginius, kad pasiimtumėte naujų."
L.dna_decayed     = "Žudiko DNR mėginys suiro."
L.dna_killer      = "Iš šio kūno surinkote žudiko DNR mėginį!"
L.dna_no_killer   = "DNR mėginys negali būti surinktas (žudikas paliko serverį?)."
L.dna_armed       = "Ši bomba vis dar veikia! Pirmiausia ją išminuokite!"
L.dna_object      = "Surinkta naujų DNR mėginių: {num}."
L.dna_gone        = "DNR šioje vietoje nerasta."

L.dna_desc        = [[
Surinkite DNR mėginius iš daiktų ir
panaudokite juos, kad surastumėte savininką.

Naudokite skaitytuvą ant šviežių kūnų,
kad surinktumėte žudiko DNR mėginį
ir jį surastumėte.]]

L.dna_menu_title  = "DNR paieškos valdymas"
L.dna_menu_sample = "DNR šaltinis: {source}"
L.dna_menu_remove = "Šalinti"
L.dna_menu_help1  = "Tai yra DNR mėginiai, kuriuos surinkote."
L.dna_menu_help2  = [[
          Kai įkrautas, galite surasti žaidėjo vietą 
          su jo DNR mėginiu. Kuo toliau taikinys, 
          tuo daugiau energijos sueikvos.]]

L.dna_menu_scan   = "Paieška"
L.dna_menu_repeat = "Autom. kartojimas"
L.dna_menu_ready  = "PARUOŠTA"
L.dna_menu_charge = "ĮKROVIMAS"
L.dna_menu_select = "PASIRINKITE MĖGINĮ"

L.dna_help_primary   = "{primaryfire}: surinkti DNR mėginį."
L.dna_help_secondary = "{secondaryfire}: atidaryti valdymo meniu."

-- Magneto stick
L.magnet_name     = "Magneta-lazda"
L.magnet_help     = "{primaryfire}: pritvirtinti kūną prie paviršiaus."

-- Grenades and misc
L.grenade_smoke   = "Dūminė granata"
L.grenade_fire    = "Padegamoji granata"

L.unarmed_name    = "Nieko"
L.crowbar_name    = "Laužtuvas"
L.pistol_name     = "Pistoletas"
L.rifle_name      = "Graižtvinis šautuvas"
L.shotgun_name    = "Lygiavamzdis šautuvas"

-- Teleporter
L.tele_name       = "Teleportas"
L.tele_failed     = "Teleportuotis nepavyko."
L.tele_marked     = "Teleportacijos vieta pažymėta."

L.tele_no_ground  = "Teleportacija galima tik ant tvirto paviršiaus!"
L.tele_no_crouch  = "Teleportacija galima tik stovint!"
L.tele_no_mark    = "Teleportacijos vieta nepažymėta. Ją pažymėkite prieš teleportaciją."

L.tele_no_mark_ground = "Pažymėti teleportacijos vietą galima tik ant tvirto paviršiaus!"
L.tele_no_mark_crouch = "Pažymėti teleportacijos vietą galima tik stovint!"

L.tele_help_pri   = "{primaryfire}: teleportuotis į pažymėtą vietą."
L.tele_help_sec   = "{secondaryfire}: pažymėti dabartinę vietą kaip teleportacijos vietą."

L.tele_desc       = [[
Teleportuoja į anksčiau pažymėtą vietą.

Teleportacija skleidžia garsą, o
naudojimų skaičius yra ribotas.]]

-- Ammo names, shown when picked up
L.ammo_pistol     = "9 mm šoviniai"

L.ammo_smg1       = "Pistoleto-kulkosvaidžio šoviniai"
L.ammo_buckshot   = "Lygiavamzdžio šautuvo šoviniai"
L.ammo_357        = "Graižtvinio šautuvo šoviniai"
L.ammo_alyxgun    = "Deagle šoviniai"
L.ammo_ar2altfire = "Signalinio pistoleto šoviniai"
L.ammo_gravity    = "Poltergeisto šoviniai"


--- HUD interface text

-- Round status
L.round_wait   = "Laukimas"
L.round_prep   = "Pasiruošimas"
L.round_active = "Eigoje"
L.round_post   = "Pabaiga"

-- Health, ammo and time area
L.overtime     = "PAPILDOMAS LAIKAS"
L.hastemode    = "SKUBĖJIMO REŽIMAS"

-- TargetID health status
L.hp_healthy   = "Sveikas"
L.hp_hurt      = "Šiek tiek sužeistas"
L.hp_wounded   = "Sužeistas"
L.hp_badwnd    = "Sunkiai sužeistas"
L.hp_death     = "Arti mirties"


-- TargetID karma status
L.karma_max    = "Gerbiamas"
L.karma_high   = "Mažai gerbiamas"
L.karma_med    = "Lengvabūdiškas"
L.karma_low    = "Pavojingas"
L.karma_min    = "Neatsakingas"

-- TargetID misc
L.corpse       = "Lavonas"
L.corpse_hint  = "{usekey}: apžiūrėti lavoną. {walkkey} + {usekey}: slaptai apžiūrėti lavoną."

L.target_disg  = " (UŽSIMASKAVĘS)"
L.target_unid  = "Neatpažintas kūnas"

L.target_traitor = "IŠDAVIKAS"
L.target_detective = "DETEKTYVAS"

L.target_credits = "Apžiūrėkite kūną, kad gautumėte nepanaudotus kreditus."

-- Traitor buttons (HUD buttons with hand icons that only traitors can see)
L.tbut_single  = "Vienkartinis naudojimas"
L.tbut_reuse   = "Daugkartinis naudojimas"
L.tbut_retime  = "Galima pakartotinai naudoti po {num} sek."
L.tbut_help    = "Spustelėkite {key}, kad aktyvintumėte."

-- Equipment info lines (on the left above the health/ammo panel)
L.disg_hud     = "Esate užsimaskavę. Informacija apie jus yra paslėpta."
L.radar_hud    = "Radaras įsikraus po {time}"

-- Spectator muting of living/dead
L.mute_living  = "Nutildyti: gyvi"
L.mute_specs   = "Nutildyti: mirę"
L.mute_all     = "Nutildyti: visi"
L.mute_off     = "Niekas nenutildytas"

-- Spectators and prop possession
L.punch_title  = "Jėgomatis"
L.punch_help   = "Valdymo klavišai arba šuolis: stumti daiktą. Pritūpimo klavišas: palikti daiktą."
L.punch_bonus  = "Jūsų taškų skaičius sumažino jėgomačio ribą iki {num}."
L.punch_malus  = "Jūsų taškų skaičius padidino jėgomačio ribą iki {num}!"

L.spec_help    = "Spustelėkite pelyte, kad stebėtumėte žaidėjus. Spustelėkite {usekey}, kad įsikūnytumėte į žiūrimą daiktą."

--- Info popups shown when the round starts

-- These are spread over multiple lines, hence the square brackets instead of
-- quotes. That's a Lua thing. Every line break (enter) will show up in-game.
L.info_popup_innocent = [[Jūs esate nekaltas teroristas! Bet aplink yra išdavikai...
Kuo galite pasitikėti ir ko verčiau vengti?

Dairykites aplinkui ir bendradarbiaukite su savo draugais, kad išliktumėte gyvi!]]

L.info_popup_detective = [[Jūs esate detektyvas! Štabas jums davė specialią įrangą, kad surastumėte išdavikus.
Naudokite ją, kad padėtumėte nekaltiems išgyventi. Tačiau būkite atsargūs,
nes išdavikai pirmiausia bandys nužudyti jus!

Spustelėkite {menukey}, jei norite nusipirkti specialios įrangos!]]

L.info_popup_traitor_alone = [[Jūs esate išdavikas! Šiame raunde neturite partnerių.

Nužudykite visus, kad laimėtumėte!

Spustelėkite {menukey}, jei norite nusipirkti specialios įrangos!]]

L.info_popup_traitor = [[Jūs esate išdavikas! Bendradarbiaukite su savo partneriais.
Tačiau būkite atsargūs, nes kitaip jūsų išdavystė bus atskleista...

Jūsų partneriai:
{traitorlist}

Spustelėkite {menukey}, jei norite nusipirkti specialios įrangos!]]

--- Various other text
L.name_kick = "Žaidėjas buvo automatiškai išmestas už vardo keitimą raundo metu."

L.idle_popup = [[Buvote neaktyvūs {num} sek., todėl buvote perkelti į stebėjimo režimą. Būdami šiame režime, neprisikelsite, kai prasidės raundas.

Galite išjungti šį režimą spustelėję {helpkey} ir panaikindami žymėjimą nustatymų skirtuke. Taip pat galite jį išjungti dabar.]]

L.idle_popup_close = "Uždaryti"
L.idle_popup_off   = "Išjungti stebėjimo režimą"

L.idle_warning = "Įspėjimas: būsite perkelti į stebėjimo režimą už ilgalaikį neveikimą, jei neparodysite savo aktyvumo!"

L.spec_mode_warning = "Esate stebėjimo režime ir neprisikelsite, kai prasidės raundas. Norėdami išjungti šį režimą, spustelėkite F1, pereikite į nustatymų skirtuką ir pašalinkite žymėjimą nustatyme „Stebėjimo režimas“."


--- Tips, shown at bottom of screen to spectators

-- Tips panel
L.tips_panel_title = "Patarimai"
L.tips_panel_tip   = "Patarimas:"

-- Tip texts

L.tip1 = "Laikydami {walkkey} ir spustelėdami {usekey} galite slaptai apžiūrėti kūną, nepatvirtindami žaidėjo mirties."

L.tip2 = "C4 užtaisymas ilgesniam laikui padidins laidų, sukeliančių sprogimą, skaičių. Be to, pypsėjimas bus tylesnis ir retesnis."

L.tip3 = "Detektyvai gali apžiūrėti kūną ir sužinoti, kas atsispindėjo aukos akyse. Tai bus paskutinis žmogus, kurį matė auka, bet tai nereiškia, kad jis yra žudikas, nes auka galėjo būti nužudyta iš nugaros."

L.tip4 = "Niekas nežinos, kad mirėte, kol jūsų kūnas nebus rastas ir atpažintas."

L.tip5 = "Kai išdavikas nužudo detektyvą, jis iškart gauna kreditinį atlygį."

L.tip6 = "Mirus išdavikui, visi detektyvai gauna kreditinį atlygį."

L.tip7 = "Kai išdavikai nužudo kelis nekaltus žmones, jie gauna kreditinį atlygį."

L.tip8 = "Išdavikai ir detektyvai gali gauti nepanaudotus kreditus iš kitų išdavikų ar detektyvų kūnų."

L.tip9 = "Poltergeistas gali paversti bet kokį fizinį objektą mirtinu sviediniu. Kiekvienas pastūmimas yra lydimas energijos sprogimu, darančiu daug žalos."

L.tip10 = "Būdami išdaviku ar detektyvu, atkreipkite dėmesį į raudonus pranešimus viršutiniame dešiniajame kampe. Juose pateikiama svarbi informacija."

L.tip11 = "Būdami išdaviku ar detektyvu, atminkite, kad gaunate kreditus, jei jūs ir jūsų partneriai gerai atliekate užduotį. Taip pat nepamirškite jų išleisti!"

L.tip12 = "DNR skaitytuvas gali būti naudojamas ginklų ar daiktų DNR mėginių surinkimui ir tada mėginio savininko vietos suradimui. Naudinga, kai galite surinkti mėginį iš kūno ar išminuotos bombos!"

L.tip13 = "Kai esate arti žmogaus, kurį žudote, dalis jūsų DNR lieka ant jo kūno. Ši DNR gali būti panaudota su DNR skaitytuvo pagalba jūsų vietos suradimui. Geriau paslėpkite žmogaus kūną po jo nužudymo!"

L.tip14 = "Kuo toliau esate nuo to žmogaus, kurį nužudėte, tuo greičiau jūsų DNR mėginys, esantis ant jo kūno, iširs."

L.tip15 = "Esate išdavikas ir ketinate būti snaiperiu? Išbandykite maskuotę. Jei nepataikysite, nubėkite į saugią vietą, įjunkite maskuotę ir niekas nežinos, kad būtent jūs šaudėte į juos."

L.tip16 = "Būdami išdaviku, teleportas gali padėti pabėgti nuo persekiotojų arba greitai judėti dideliame žemėlapyje. Nepamirškite pažymėti saugią teleportacijos vietą."

L.tip17 = "Visi nekalti teroristai yra vienoje vietoje ir juos sunku atskirti? Pabandykite atitraukti kelių iš jų dėmesį su radijo šaudymo arba C4 pypsėjimo garsais."

L.tip18 = "Būdami išdaviku, po radijo padėjimo galite leisti garsus įrangos meniu. Galite sukurti garsų eilę spustelėdami ant jų norima tvarka."

L.tip19 = "Būdami detektyvu, jei turite kreditų, patikimam nekaltam teroristui galite atiduoti išminavimo rinkinį. Taip galėsite užsiimti rimtais darbais, o jis užsiims bombos išminavimu."

L.tip20 = "Žiūronai leidžia iš tolo apžiūrėti ir atpažinti kūnus. Bloga žinia išdavikams, jei jie tikėjosi naudoti kūną viliojimui. Žinoma, naudodami žiūronus esate be ginklo ir jūsų dėmesys yra atitrauktas..."

L.tip21 = "Gydymo stotelė leidžia sužeistiems žaidėjams atgauti sveikatos. Žinoma, šie žaidėjai gali taip pat būti ir išdavikai..."

L.tip22 = "Gydymo stotelė renka DNR mėginius iš visų žmonių, kurie ją panaudojo. Detektyvai gali panaudoti mėginius su DNR skaitytuvu, kad rastų tuos, kurie ją panaudojo."

L.tip23 = "Skirtingai nuo ginklų ir C4, radijas neturi jį padėjusio žmogaus DNR mėginio. Nesijaudinkite dėl galimo atskleidimo, jei jūsų radiją rado detektyvai."

L.tip24 = "Spustelėkite {helpkey}, kad peržiūrėtumėte trumpą instrukciją arba pakeistumėte kai kuriuos TTT nustatymus. Pavyzdžiui, galite išjungti šiuos patarimus."

L.tip25 = "Kai detektyvas apžiūri kūną, apžiūrėjimo rezultatai yra visiems pasiekiami spustelint ant mirusio žmogaus vardo taškų lentelėje."

L.tip26 = "Didinamojo stiklo piktograma taškų lentelėje šalia kieno nors vardo reiškia, kad turite to žmogaus apžiūrėjimo rezultatus. Jei piktograma ryški, rezultatai yra gauti iš detektyvo ir gali turėti papildomos informacijos."

L.tip27 = "Lavonai, turintys savo vardo gale didinamojo stiklo piktogramą, yra apžiūrėti detektyvo ir apžiūrėjimo rezultatai yra prieinami visiems žaidėjams taškų lentelėje."

L.tip28 = "Stebėtojai gali spustelėti {mutekey}, kad nutildytų kitus stebėtojus, gyvus ar net visus žaidėjus."

L.tip29 = "Jei serveryje yra įdiegtos papildomos kalbos, jas galite pasirinkti nustatymų meniu."

L.tip30 = "Galite naudoti sparčiuosius pranešimus spustelėdami {zoomkey}."

L.tip31 = "Būdami stebėtoju, spustelėkite {duckkey}, kad įjungtumėte žymeklį ir spustelėkite šiame skyde esantį mygtuką. Spustelėkite {duckkey} dar kartą, kad išjungtumėte žymeklį."

L.tip32 = "Laužtuvo papildomas puolimas stumia žaidėjus."

L.tip33 = "Priešingai nei šaudymas pritūpus, šaudymas su taikikliu šiek tiek padidina tikslumą ir sumažina atatranką."

L.tip34 = "Dūminės granatos yra veiksmingos patalpose, ypač tada, kai sukuria sumaištį žmonių perpildytoje patalpoje."

L.tip35 = "Būdami išdaviku, nepamirškite, kad galite slėpti kūnus nuo nekaltų ir detektyvų smalsių akių."

L.tip36 = "Instrukcija, pasiekiama spustelėjus {helpkey}, turi informacijos apie pačius svarbiausius žaidimo ypatumus."

L.tip37 = "Taškų lentelėje galite spustelėti ant gyvo žaidėjo vardo ir priskirti jam tokias žymes, kaip „įtariamasis“ arba „draugas“. Ši žymė pasirodys po jūsų kryžme, jei užvesite pelę ant žaidėjo."

L.tip38 = "Dauguma padedamosios įrangos, pavyzdžiui, C4 arba radijas, gali būti pritvirtintos prie sienų su papildomu puolimo klavišu."

L.tip39 = "C4, sprogęs dėl nepavykusio išminavimo bandymo, turi mažesnį sprogimo spindulį nei C4, kuris sprogo pasibaigus laikmačiui."

L.tip40 = "Jei po laikmačiu parašyta „Skubėjimo režimas“, iš pirmo raundas truks tik kelias minutes, tačiau su kiekviena mirtimi laikas ilgės. Šis režimas suteikia išdavikams spaudimą, todėl juos priverčia veikti."


--- Round report

L.report_title = "Raundo ataskaita"

-- Tabs
L.report_tab_hilite = "Pagrindiniai momentai"
L.report_tab_hilite_tip = "Raundo pagrindiniai momentai."
L.report_tab_events = "Įvykiai"
L.report_tab_events_tip = "Šio raundo įvykių žurnalas."
L.report_tab_scores = "Rezultatas"
L.report_tab_scores_tip = "Taškai, pelnyti kiekvieno žaidėjo šiame raunde."

-- Event log saving
L.report_save     = "Išsaugoti"
L.report_save_tip = "Išsaugo įvykių žurnalą į tekstinį failą."
L.report_save_error  = "Nėra įvykių žurnalo duomenų, kad būtų galima išsaugoti."
L.report_save_result = "Įvykių žurnalas išsaugotas:"

-- Big title window
L.hilite_win_traitors = "IŠDAVIKŲ PERGALĖ"
L.hilite_win_innocent = "NEKALTŲ PERGALĖ"

L.hilite_players1 = "Iš {numplayers} žaidėjų, {numtraitors} buvo išdavikai."
L.hilite_players2 = "Iš {numplayers} žaidėjų, vienas buvo išdavikas."

L.hilite_duration = "Raundas truko {time}"

-- Columns
L.col_time   = "Laikas"
L.col_event  = "Įvykis"
L.col_player = "Žaidėjas"
L.col_role   = "Vaidmuo"
L.col_kills1 = "Nužudyta nekaltų"
L.col_kills2 = "Nužudyta išdavikų"
L.col_points = "Taškai"
L.col_team   = "Komandinis bonusas"
L.col_total  = "Iš viso"

-- Name of a trap that killed us that has not been named by the mapper
L.something      = "kažkas"

-- Kill events
L.ev_blowup      = "{victim} save susprogdina."
L.ev_blowup_trap = "{victim} sprogsta nuo {trap}."

L.ev_tele_self   = "{victim} save nusižudo su teleportu."
L.ev_sui         = "{victim} neiškenčia ir nusižudo."
L.ev_sui_using   = "{victim} nusižudo su {tool}."

L.ev_fall        = "{victim} nukrenta iki mirties."
L.ev_fall_pushed = "{victim} nukrenta iki mirties po {attacker} pastūmimo."
L.ev_fall_pushed_using = "{victim} nukrenta iki mirties po {trap}, aktyvinto {attacker}, pastūmimo."

L.ev_shot        = "{attacker} nušauna {victim}."
L.ev_shot_using  = "{attacker} nušauna {victim} su {weapon}."

L.ev_drown       = "{attacker} nuskandina {victim}."
L.ev_drown_using = "{attacker} nuskandina {victim} su {trap}."

L.ev_boom        = "{attacker} susprogdina {victim}."
L.ev_boom_using  = "{attacker} susprogdina {victim} su {trap}."

L.ev_burn        = "{attacker} sudegina {victim}."
L.ev_burn_using  = "{attacker} sudegina {victim} su {trap}."

L.ev_club        = "{attacker} sumuša {victim}."
L.ev_club_using  = "{attacker} sumuša {victim} su {trap}."

L.ev_slash       = "{attacker} nuduria {victim}."
L.ev_slash_using = "{attacker} nuduria {victim} su {trap}."

L.ev_tele        = "{attacker} teleportacija nužudo {victim}."
L.ev_tele_using  = "{trap}, padėtas {attacker}, susmulkina {victim} iki atomų."

L.ev_goomba      = "{attacker} sutraiško {victim} su savo mase."

L.ev_crush       = "{attacker} sutraiško {victim}."
L.ev_crush_using = "{attacker} sutraiško {victim} su {trap}."

L.ev_other       = "{attacker} nužudo {victim}."
L.ev_other_using = "{attacker} nužudo {victim} su {trap}."

-- Other events
L.ev_body        = "{finder} randa {victim} kūną."
L.ev_c4_plant    = "{player} užtaiso C4."
L.ev_c4_boom     = "{player} užtaisytas C4 susprogsta."
L.ev_c4_disarm1  = "{player} išminuoja {owner} užtaisytą C4."
L.ev_c4_disarm2  = "{player} nesugeba išminuoti {owner} užtaisytą C4."
L.ev_credit      = "{finder} rado {num} kreditą (-us/-ų) ant {player} kūno."

L.ev_start       = "Prasideda raundas."
L.ev_win_traitor = "Laimi niekšiški išdavikai!"
L.ev_win_inno    = "Laimi visų mylimiausi nekalti teroristai!"
L.ev_win_time    = "Išdavikam pritrūksta laiko ir pralaimi!"

--- Awards/highlights

L.aw_sui1_title = "Savižudybės kulto vadovas"
L.aw_sui1_text  = "nusižudydamas kitiems savižudžiams parodė, kaip tai reikia padaryti."

L.aw_sui2_title = "Vienišas ir prislėgtas"
L.aw_sui2_text  = "buvo vienintelis, kuris nusižudė."

L.aw_exp1_title = "Dotacija sprogmenų tyrimams"
L.aw_exp1_text  = "buvo pripažintas už sprogmenų tyrimus. {num} bandomieji (-ųjų) subjektai (-ų) jam padėjo."

L.aw_exp2_title = "Tyrimas mūšio lauke"
L.aw_exp2_text  = "išbandė savo atsparumą sprogimams. Jo nepakako."

L.aw_fst1_title = "Pirmasis kraujas"
L.aw_fst1_text  = "įvykdė pirmąjį nekalto teroristo nužudymą išdaviko rankose."

L.aw_fst2_title = "Pirmasis be galo kvailas nužudymas"
L.aw_fst2_text  = "įvykdė pirmąjį nužudymą nužudydamas kitą išdaviką. Neblogai padirbėta!"

L.aw_fst3_title = "Pirmoji klaida"
L.aw_fst3_text  = "buvo pirmas, kuris nužudė žmogų. Labai blogai, nes jis buvo nekaltas."

L.aw_fst4_title = "Pirmasis smūgis"
L.aw_fst4_text  = "sudavė pirmąjį smūgį nekaltų teroristų naudai, nužudė išdaviką."

L.aw_all1_title = "Pats mirtingiausias tarp lygių"
L.aw_all1_text  = "buvo atsakingas už kiekvieną nekaltų teroristų įvykdytą nužudymą."

L.aw_all2_title = "Vienišas vilkas"
L.aw_all2_text  = "buvo atsakingas už kiekvieną išdavikų įvykdytą nužudymą."

L.aw_nkt1_title = "Vienas gatavas, bose!"
L.aw_nkt1_text  = "sugebėjo nužudyti vieną nekaltą teroristą. Miela!"

L.aw_nkt2_title = "Kulka dviem"
L.aw_nkt2_text  = "nužudydamas kitą parodė, kad pirmasis šūvis buvo nesėkmingas."

L.aw_nkt3_title = "Serijinis išdavikas"
L.aw_nkt3_text  = "šiandien nutraukė trijų nekaltų teroristų gyvybes."

L.aw_nkt4_title = "Vilkas tarp daugiau į avis panašių vilkų"
L.aw_nkt4_text  = "vakarienei valgo nekaltus teroristus. Vakarienė iš {num} kūnų."

L.aw_nkt5_title = "Kontrteroristinė operacija"
L.aw_nkt5_text  = "gauna pinigus už nužudymus ir dabar gali nusipirkti dar vieną prabangią jachtą."

L.aw_nki1_title = "Išduok šitą"
L.aw_nki1_text  = "rado išdaviką. Jį nušovė. Negali būti lengviau."

L.aw_nki2_title = "Priimtas į teisingumo būrį"
L.aw_nki2_text  = "palydėjo du išdavikus į požeminį pasaulį."

L.aw_nki3_title = "Ar išdavikai svajoja apie išdavikes avis?"
L.aw_nki3_text  = "užmigdė tris išdavikus."

L.aw_nki4_title = "Vidaus reikalų darbuotojas"
L.aw_nki4_text  = "gauna pinigus už nužudymus ir dabar gali nusipirkti penktąjį baseiną."

L.aw_fal1_title = "Ne, pone Bondai, aš laukiu, kada jūs nukrisite"
L.aw_fal1_text  = "nustūmė ką nors iš didelio aukščio."

L.aw_fal2_title = "Įžemintas"
L.aw_fal2_text  = "leido savo kūnui iš didelio aukščio nukristi tiesiai į žemę."

L.aw_fal3_title = "Žmogus-meteoritas"
L.aw_fal3_text  = "krisdamas iš didelio aukščio kažką sutraiškė."

L.aw_hed1_title = "Veiksmingumas"
L.aw_hed1_text  = "šaudymas į galvą suteikia malonumą, todėl į galvą šovė {num} kartus (-ų)."

L.aw_hed2_title = "Neurologija"
L.aw_hed2_text  = "pašalino smegenis iš {num} galvų tyrimams."

L.aw_hed3_title = "Vaizdo žaidimai privertė mane tai padaryti"
L.aw_hed3_text  = "pritaikė žinias, įgytas maniako simuliatoriuje, ir šovė {num} priešam į galvą."

L.aw_cbr1_title = "Tuk, tuk, tuk"
L.aw_cbr1_text  = "turi vidutinį užmojį su laužtuvu, kaip suprato {num} aukos (-ų)."

L.aw_cbr2_title = "Frimenas"
L.aw_cbr2_text  = "išpurvino savo laužtuvą smegenimis ne mažiau {num} žmonių."

L.aw_pst1_title = "Atkaklus mažas vaikpalaikis"
L.aw_pst1_text  = "įvykdė {num} nužudymus (-ų) pistoletu, o tada nuėjo apkabinti ką nors iki mirties."

L.aw_pst2_title = "Mažo kalibro žudynės"
L.aw_pst2_text  = "nužudė {num} žmones (-ių) su pistoletu. Tikriausiai vamzdyje įrengė mažytį lygiavamzdį šautuvą."

L.aw_sgn1_title = "Lengvas režimas"
L.aw_sgn1_text  = "taiko šratus ten, kur skauda, nužudydamas {num} taikinius (-ių)."

L.aw_sgn2_title = "Tūkstantis šratų"
L.aw_sgn2_text  = "nelabai mylėjo savo šratus, todėl visus juos atidavė. {num} gavėjam nepavyko išgyventi."

L.aw_rfl1_title = "Nusitaikyk ir šauk"
L.aw_rfl1_text  = "parodė, kad šautuvas ir tvirta ranka yra viskas, ko reikia, norint nužudyti {num} žmones (-ių)."

L.aw_rfl2_title = "Aš iš čia matau tavo galvą"
L.aw_rfl2_text  = "žino savo šautuvą. Dabar {num} kiti (-ų) žmones (-ių) jį taip žino."

L.aw_dgl1_title = "Tai tarsi mažas šautuvas"
L.aw_dgl1_text  = "nušovė {num} žmones (-ių) su desert eagle."

L.aw_dgl2_title = "Deagle meistras"
L.aw_dgl2_text  = "nužudė {num} žmones (-ių) su desert eagle."

L.aw_mac1_title = "Melskis ir žudyk"
L.aw_mac1_text  = "nužudė {num} žmones (-ių) su MAC10, bet nepasakys, kiek šovinių prireikė."

L.aw_mac2_title = "Makaronai su sūriu"
L.aw_mac2_text  = "įdomu, kiek žmonių mirtų nuo jo rankų su dviem MAC10. {num} kart du?"

L.aw_sip1_title = "Tyliau"
L.aw_sip1_text  = "nužudė {num} žmones (-ių) naudojant pistoletą su duslintuvu."

L.aw_sip2_title = "Tylus žudikas"
L.aw_sip2_text  = "nužudė {num} žmones (-ių), kurie negirdėjo savo mirties."

L.aw_knf1_title = "Peilis tave pažįsta"
L.aw_knf1_text  = "kažkam įsmeigė peilį į veidą per internetą."

L.aw_knf2_title = "Iš kur tai gavai?"
L.aw_knf2_text  = "nebuvo išdavikas, bet vis tiek nužudė kažką su peiliu."

L.aw_knf3_title = "Ant tiek peilinis žmogus"
L.aw_knf3_text  = "rado {num} gulinčius (-ių) peilius (-ių) ir juos panaudojo."

L.aw_knf4_title = "Peiliniausias žmogus pasaulyje"
L.aw_knf4_text  = "nužudė {num} žmones (-ių) su peiliu. Neklauskite, kaip."

L.aw_flg1_title = "Į pagalbą"
L.aw_flg1_text  = "panaudojo signalines raketas, kad iškviestų pagalbą, bet sudegino {num} žmones (-ių)."

L.aw_flg2_title = "Signalinė raketa reiškia ugnį"
L.aw_flg2_text  = "papasakojo {num} žmonėms apie degių drabužių dėvėjimo pavojų."

L.aw_hug1_title = "Mažas glaustumas"
L.aw_hug1_text  = "buvo harmonijoje su savo H.U.G.E., kažkaip sugebėjo pataikyti į {num} žmones (-ių)."

L.aw_hug2_title = "Kantri pora"
L.aw_hug2_text  = "nenustojo šaudyti su savo H.U.G.E. ir pastebėjo, kad jo kantrybė buvo atlyginta {num} nužudymais."

L.aw_msx1_title = "Pop, pop, pop"
L.aw_msx1_text  = "nužudė {num} žmones (-ių) su M16."

L.aw_msx2_title = "Vidutinio nuotolio beprotybė"
L.aw_msx2_text  = "žino, kaip žudyti su M16, todėl nužudė {num} žmones (-ių)."

L.aw_tkl1_title = "Oi!"
L.aw_tkl1_text  = "nuspaudė gaiduką tada, kai taikėsi į savo draugą."

L.aw_tkl2_title = "Oi, oi!"
L.aw_tkl2_text  = "dukart galvojo, kad jis yra išdavikas, bet abiejuose atvejuose klydo."

L.aw_tkl3_title = "Suprantantis karmą"
L.aw_tkl3_text  = "negalėjo sustoti po dviejų draugų nužudymo. Trys - laimingas skaičius."

L.aw_tkl4_title = "Draugų žudikas"
L.aw_tkl4_text  = "nužudė visą savo komandą. O DIEVE!"

L.aw_tkl5_title = "Vaidmenų žaidėjas"
L.aw_tkl5_text  = "vaidino psichą, tikrai. Štai kodėl jis nužudė didžiąją dalį savo komandos."

L.aw_tkl6_title = "Kvailys"
L.aw_tkl6_text  = "nesugebėjo suprasti, kurioje pusėje jis yra, todėl nužudė pusę savo draugų."

L.aw_tkl7_title = "Prasčiokas"
L.aw_tkl7_text  = "labai gerai apsaugojo savo teritoriją, nužudydamas daugiau nei ketvirtadalį savo draugų."

L.aw_brn1_title = "Pagal močiutės receptą"
L.aw_brn1_text  = "iškepė kelis žmones iki traškesio."

L.aw_brn2_title = "Piromanija"
L.aw_brn2_text  = "išgirdo garsų karkimą po vieno iš daugelio jo aukų sudeginimo."

L.aw_brn3_title = "Pyro sudeginimas"
L.aw_brn3_text  = "sudegino juos visus, bet pritrūko padegamųjų granatų. Kaip jis su tuo susitvarkys?"

L.aw_fnd1_title = "Koroneris"
L.aw_fnd1_text  = "rado {num} kūnus (-ų)."

L.aw_fnd2_title = "Turiu surasti juos visus"
L.aw_fnd2_text  = "rado {num} kūnus (-ų) savo kolekcijai."

L.aw_fnd3_title = "Mirties kvapas"
L.aw_fnd3_text  = "toliau užkliuvinėja ant atsitiktinių kūnų, {num} kartus (-ų) šiame raunde."

L.aw_crd1_title = "Perdirbėjas"
L.aw_crd1_text  = "nuo kūnų surinko {num} nepanaudotus (-ų) kreditus (-ų)."

L.aw_tod1_title = "Pyro pergalė"
L.aw_tod1_text  = "mirė likus vos kelioms sekundėms iki savo komandos pergalės."

L.aw_tod2_title = "Aš nekenčiu šio žaidimo"
L.aw_tod2_text  = "mirė iškart po raundo pradžios."


--- New and modified pieces of text are placed below this point, marked with the
--- version in which they were added, to make updating translations easier.


--- v23
L.set_avoid_det     = "Vengti būti detektyvu"
L.set_avoid_det_tip = "Įjunkite, kad serveris, jei įmanoma, nepasirinktų jūsų kaip detektyvo. Tai nereiškia, kad jūs būsite išdaviku dažniau."

--- v24
L.drop_no_ammo = "Apkaboje nepakanka šovinių, kad juos būtų galima išmesti kaip dėžę su šoviniais."

--- v31
L.set_cross_brightness = "Kryžmės ryškumas"
L.set_cross_size = "Kryžmės dydis"

--- 5-25-15
L.hat_retrieve = "Pasiėmėte detektyvo kepurę"

--- 3-9-2017
L.sb_sortby = "Rikiuoti:"

--- 2018-07-24
L.equip_tooltip_main = "Įrangos meniu"
L.equip_tooltip_radar = "Radaro valdymas"
L.equip_tooltip_disguise = "Maskuotės valdymas"
L.equip_tooltip_radio = "Radijo valdymas"
L.equip_tooltip_xfer = "Kreditų perdavimas"

L.confgrenade_name = "Atstumiančioji granata"
L.polter_name = "Poltergeistas"
L.stungun_name = "UMP prototipas"

L.knife_instant = "AKIMIRKSNIŠKAS NUŽUDYMAS"

L.dna_hud_type = "RŪŠIS"
L.dna_hud_body = "KŪNAS"
L.dna_hud_item = "DAIKTAS"

L.binoc_zoom_level = "LYGIS"
L.binoc_body = "APTIKTAS KŪNAS"

L.idle_popup_title = "Neveikimas"