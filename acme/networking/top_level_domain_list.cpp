﻿#include "framework.h"


const char8_t * g_pszTopLevelDomainList[] = 
{
u8"aaa (aaa)	",
u8"aarp (aarp)	",
u8"abarth (abarth)	",
u8"abb (abb)	",
u8"abbott (abbott)	",
u8"abbvie (abbvie)	",
u8"abc (abc)	",
u8"able (able)	",
u8"abogado (abogado)	",
u8"abudhabi (abudhabi)	",
u8"ac (ac)	",
u8"academy (academy)	",
u8"accenture (accenture)	",
u8"accountant (accountant)	",
u8"accountants (accountants)	",
u8"aco (aco)	",
u8"active (active)	",
u8"actor (actor)	",
u8"ad (ad)	",
u8"adac (adac)	",
u8"ads (ads)	",
u8"adult (adult)	",
u8"ae (ae)	",
u8"aeg (aeg)	",
u8"aero (aero)	",
u8"aetna (aetna)	",
u8"af (af)	",
u8"afamilycompany (afamilycompany)	",
u8"afl (afl)	",
u8"africa (africa)	",
u8"ag (ag)	",
u8"agakhan (agakhan)	",
u8"agency (agency)	",
u8"ai (ai)	",
u8"aig (aig)	",
u8"aigo (aigo)	",
u8"airbus (airbus)	",
u8"airforce (airforce)	",
u8"airtel (airtel)	",
u8"akdn (akdn)	",
u8"al (al)	",
u8"alfaromeo (alfaromeo)	",
u8"alibaba (alibaba)	",
u8"alipay (alipay)	",
u8"allfinanz (allfinanz)	",
u8"allstate (allstate)	",
u8"ally (ally)	",
u8"alsace (alsace)	",
u8"alstom (alstom)	",
u8"am (am)	",
u8"americanexpress (americanexpress)	",
u8"americanfamily (americanfamily)	",
u8"amex (amex)	",
u8"amfam (amfam)	",
u8"amica (amica)	",
u8"amsterdam (amsterdam)	",
u8"analytics (analytics)	",
u8"android (android)	",
u8"anquan (anquan)	",
u8"anz (anz)	",
u8"ao (ao)	",
u8"aol (aol)	",
u8"apartments (apartments)	",
u8"app (app)	",
u8"apple (apple)	",
u8"aq (aq)	",
u8"aquarelle (aquarelle)	",
u8"ar (ar)	",
u8"arab (arab)	",
u8"aramco (aramco)	",
u8"archi (archi)	",
u8"army (army)	",
u8"arpa (arpa)	",
u8"art (art)	",
u8"arte (arte)	",
u8"as (as)	",
u8"asda (asda)	",
u8"asia (asia)	",
u8"associates (associates)	",
u8"at (at)	",
u8"athleta (athleta)	",
u8"attorney (attorney)	",
u8"au (au)	",
u8"auction (auction)	",
u8"audi (audi)	",
u8"audible (audible)	",
u8"audio (audio)	",
u8"auspost (auspost)	",
u8"author (author)	",
u8"auto (auto)	",
u8"autos (autos)	",
u8"avianca (avianca)	",
u8"aw (aw)	",
u8"aws (aws)	",
u8"ax (ax)	",
u8"axa (axa)	",
u8"az (az)	",
u8"azure (azure)	",
u8"ba (ba)	",
u8"baby (baby)	",
u8"baidu (baidu)	",
u8"banamex (banamex)	",
u8"bananarepublic (bananarepublic)	",
u8"band (band)	",
u8"bank (bank)	",
u8"bar (bar)	",
u8"barcelona (barcelona)	",
u8"barclaycard (barclaycard)	",
u8"barclays (barclays)	",
u8"barefoot (barefoot)	",
u8"bargains (bargains)	",
u8"baseball (baseball)	",
u8"basketball (basketball)	",
u8"bauhaus (bauhaus)	",
u8"bayern (bayern)	",
u8"bb (bb)	",
u8"bbc (bbc)	",
u8"bbt (bbt)	",
u8"bbva (bbva)	",
u8"bcg (bcg)	",
u8"bcn (bcn)	",
u8"bd (bd)	",
u8"be (be)	",
u8"beats (beats)	",
u8"beauty (beauty)	",
u8"beer (beer)	",
u8"bentley (bentley)	",
u8"berlin (berlin)	",
u8"best (best)	",
u8"bestbuy (bestbuy)	",
u8"bet (bet)	",
u8"bf (bf)	",
u8"bg (bg)	",
u8"bh (bh)	",
u8"bharti (bharti)	",
u8"bi (bi)	",
u8"bible (bible)	",
u8"bid (bid)	",
u8"bike (bike)	",
u8"bing (bing)	",
u8"bingo (bingo)	",
u8"bio (bio)	",
u8"biz (biz)	",
u8"bj (bj)	",
u8"black (black)	",
u8"blackfriday (blackfriday)	",
u8"blanco (blanco)	",
u8"blockbuster (blockbuster)	",
u8"blog (blog)	",
u8"bloomberg (bloomberg)	",
u8"blue (blue)	",
u8"bm (bm)	",
u8"bms (bms)	",
u8"bmw (bmw)	",
u8"bn (bn)	",
u8"bnl (bnl)	",
u8"bnpparibas (bnpparibas)	",
u8"bo (bo)	",
u8"boats (boats)	",
u8"boehringer (boehringer)	",
u8"bofa (bofa)	",
u8"bom (bom)	",
u8"bond (bond)	",
u8"boo (boo)	",
u8"book (book)	",
u8"booking (booking)	",
u8"bosch (bosch)	",
u8"bostik (bostik)	",
u8"boston (boston)	",
u8"bot (bot)	",
u8"boutique (boutique)	",
u8"box (box)	",
u8"br (br)	",
u8"bradesco (bradesco)	",
u8"bridgestone (bridgestone)	",
u8"broadway (broadway)	",
u8"broker (broker)	",
u8"brother (brother)	",
u8"brussels (brussels)	",
u8"bs (bs)	",
u8"bt (bt)	",
u8"budapest (budapest)	",
u8"bugatti (bugatti)	",
u8"build (build)	",
u8"builders (builders)	",
u8"business (business)	",
u8"buy (buy)	",
u8"buzz (buzz)	",
u8"bv (bv)	",
u8"bw (bw)	",
u8"by (by)	",
u8"bz (bz)	",
u8"bzh (bzh)	",
u8"ca (ca)	",
u8"cab (cab)	",
u8"cafe (cafe)	",
u8"cal (cal)	",
u8"call (call)	",
u8"calvinklein (calvinklein)	",
u8"cam (cam)	",
u8"camera (camera)	",
u8"camp (camp)	",
u8"cancerresearch (cancerresearch)	",
u8"canon (canon)	",
u8"capetown (capetown)	",
u8"capital (capital)	",
u8"capitalone (capitalone)	",
u8"car (car)	",
u8"caravan (caravan)	",
u8"cards (cards)	",
u8"care (care)	",
u8"career (career)	",
u8"careers (careers)	",
u8"cars (cars)	",
u8"cartier (cartier)	",
u8"casa (casa)	",
u8"case (case)	",
u8"caseih (caseih)	",
u8"cash (cash)	",
u8"casino (casino)	",
u8"cat (cat)	",
u8"catering (catering)	",
u8"catholic (catholic)	",
u8"cba (cba)	",
u8"cbn (cbn)	",
u8"cbre (cbre)	",
u8"cbs (cbs)	",
u8"cc (cc)	",
u8"cd (cd)	",
u8"ceb (ceb)	",
u8"center (center)	",
u8"ceo (ceo)	",
u8"cern (cern)	",
u8"cf (cf)	",
u8"cfa (cfa)	",
u8"cfd (cfd)	",
u8"cg (cg)	",
u8"ch (ch)	",
u8"chanel (chanel)	",
u8"channel (channel)	",
u8"chase (chase)	",
u8"chat (chat)	",
u8"cheap (cheap)	",
u8"chintai (chintai)	",
u8"christmas (christmas)	",
u8"chrome (chrome)	",
u8"chrysler (chrysler)	",
u8"church (church)	",
u8"ci (ci)	",
u8"cipriani (cipriani)	",
u8"circle (circle)	",
u8"cisco (cisco)	",
u8"citadel (citadel)	",
u8"citi (citi)	",
u8"citic (citic)	",
u8"city (city)	",
u8"cityeats (cityeats)	",
u8"ck (ck)	",
u8"cl (cl)	",
u8"claims (claims)	",
u8"cleaning (cleaning)	",
u8"click (click)	",
u8"clinic (clinic)	",
u8"clinique (clinique)	",
u8"clothing (clothing)	",
u8"cloud (cloud)	",
u8"club (club)	",
u8"clubmed (clubmed)	",
u8"cm (cm)	",
u8"cn (cn)	",
u8"co (co)	",
u8"coach (coach)	",
u8"codes (codes)	",
u8"coffee (coffee)	",
u8"college (college)	",
u8"cologne (cologne)	",
u8"com (com)	",
u8"comcast (comcast)	",
u8"commbank (commbank)	",
u8"community (community)	",
u8"company (company)	",
u8"compare (compare)	",
u8"computer (computer)	",
u8"comsec (comsec)	",
u8"condos (condos)	",
u8"construction (construction)	",
u8"consulting (consulting)	",
u8"contact (contact)	",
u8"contractors (contractors)	",
u8"cooking (cooking)	",
u8"cookingchannel (cookingchannel)	",
u8"cool (cool)	",
u8"coop (coop)	",
u8"corsica (corsica)	",
u8"country (country)	",
u8"coupon (coupon)	",
u8"coupons (coupons)	",
u8"courses (courses)	",
u8"color32 (color32)	",
u8"credit (credit)	",
u8"creditcard (creditcard)	",
u8"creditunion (creditunion)	",
u8"cricket (cricket)	",
u8"crown (crown)	",
u8"crs (crs)	",
u8"cruise (cruise)	",
u8"cruises (cruises)	",
u8"csc (csc)	",
u8"cu (cu)	",
u8"cuisinella (cuisinella)	",
u8"cv (cv)	",
u8"cw (cw)	",
u8"cx (cx)	",
u8"cy (cy)	",
u8"cymru (cymru)	",
u8"cyou (cyou)	",
u8"cz (cz)	",
u8"dabur (dabur)	",
u8"dad (dad)	",
u8"dance (dance)	",
u8"data (data)	",
u8"date (date)	",
u8"dating (dating)	",
u8"datsun (datsun)	",
u8"day (day)	",
u8"dclk (dclk)	",
u8"dds (dds)	",
u8"de (de)	",
u8"deal (deal)	",
u8"dealer (dealer)	",
u8"deals (deals)	",
u8"degree (degree)	",
u8"delivery (delivery)	",
u8"dell (dell)	",
u8"deloitte (deloitte)	",
u8"delta (delta)	",
u8"democrat (democrat)	",
u8"dental (dental)	",
u8"dentist (dentist)	",
u8"desi (desi)	",
u8"design (design)	",
u8"dev (dev)	",
u8"dhl (dhl)	",
u8"diamonds (diamonds)	",
u8"diet (diet)	",
u8"digital (digital)	",
u8"direct (direct)	",
u8"directory (directory)	",
u8"discount (discount)	",
u8"discover (discover)	",
u8"dish (dish)	",
u8"diy (diy)	",
u8"dj (dj)	",
u8"dk (dk)	",
u8"dm (dm)	",
u8"dnp (dnp)	",
u8"do (do)	",
u8"docs (docs)	",
u8"doctor (doctor)	",
u8"dodge (dodge)	",
u8"dog (dog)	",
u8"doha (doha)	",
u8"domains (domains)	",
u8"dot (dot)	",
u8"download (download)	",
u8"drive (drive)	",
u8"dtv (dtv)	",
u8"dubai (dubai)	",
u8"duck (duck)	",
u8"dunlop (dunlop)	",
u8"duns (duns)	",
u8"dupont (dupont)	",
u8"durban (durban)	",
u8"dvag (dvag)	",
u8"dvr (dvr)	",
u8"dz (dz)	",
u8"earth (earth)	",
u8"eat (eat)	",
u8"ec (ec)	",
u8"eco (eco)	",
u8"edeka (edeka)	",
u8"edu (edu)	",
u8"education (education)	",
u8"ee (ee)	",
u8"eg (eg)	",
u8"email (email)	",
u8"emerck (emerck)	",
u8"energy (energy)	",
u8"engineer (engineer)	",
u8"engineering (engineering)	",
u8"enterprises (enterprises)	",
u8"epost (epost)	",
u8"epson (epson)	",
u8"equipment (equipment)	",
u8"er (er)	",
u8"ericsson (ericsson)	",
u8"erni (erni)	",
u8"es (es)	",
u8"esq (esq)	",
u8"estate (estate)	",
u8"esurance (esurance)	",
u8"et (et)	",
u8"etisalat (etisalat)	",
u8"eu (eu)	",
u8"eurovision (eurovision)	",
u8"eus (eus)	",
u8"events (events)	",
u8"everbank (everbank)	",
u8"exchange (exchange)	",
u8"expert (expert)	",
u8"exposed (exposed)	",
u8"express (express)	",
u8"extraspace (extraspace)	",
u8"fage (fage)	",
u8"fail (fail)	",
u8"fairwinds (fairwinds)	",
u8"faith (faith)	",
u8"family (family)	",
u8"fan (fan)	",
u8"fans (fans)	",
u8"farm (farm)	",
u8"farmers (farmers)	",
u8"fashion (fashion)	",
u8"fast (fast)	",
u8"fedex (fedex)	",
u8"feedback (feedback)	",
u8"ferrari (ferrari)	",
u8"ferrero (ferrero)	",
u8"fi (fi)	",
u8"fiat (fiat)	",
u8"fidelity (fidelity)	",
u8"fido (fido)	",
u8"film (film)	",
u8"final (final)	",
u8"finance (finance)	",
u8"financial (financial)	",
u8"fire (fire)	",
u8"firestone (firestone)	",
u8"firmdale (firmdale)	",
u8"fish (fish)	",
u8"fishing (fishing)	",
u8"fit (fit)	",
u8"fitness (fitness)	",
u8"fj (fj)	",
u8"fk (fk)	",
u8"flickr (flickr)	",
u8"flights (flights)	",
u8"flir (flir)	",
u8"florist (florist)	",
u8"flowers (flowers)	",
u8"fly (fly)	",
u8"fm (fm)	",
u8"fo (fo)	",
u8"foo (foo)	",
u8"food (food)	",
u8"foodnetwork (foodnetwork)	",
u8"football (football)	",
u8"ford (ford)	",
u8"forex (forex)	",
u8"forsale (forsale)	",
u8"forum (forum)	",
u8"foundation (foundation)	",
u8"fox (fox)	",
u8"fr (fr)	",
u8"free (free)	",
u8"fresenius (fresenius)	",
u8"frl (frl)	",
u8"frogans (frogans)	",
u8"frontdoor (frontdoor)	",
u8"frontier (frontier)	",
u8"ftr (ftr)	",
u8"fujitsu (fujitsu)	",
u8"fujixerox (fujixerox)	",
u8"fun (fun)	",
u8"fund (fund)	",
u8"furniture (furniture)	",
u8"futbol (futbol)	",
u8"fyi (fyi)	",
u8"ga (ga)	",
u8"gal (gal)	",
u8"gallery (gallery)	",
u8"gallo (gallo)	",
u8"gallup (gallup)	",
u8"game (game)	",
u8"games (games)	",
u8"gap (gap)	",
u8"garden (garden)	",
u8"gb (gb)	",
u8"gbiz (gbiz)	",
u8"gd (gd)	",
u8"gdn (gdn)	",
u8"ge (ge)	",
u8"gea (gea)	",
u8"gent (gent)	",
u8"genting (genting)	",
u8"george (george)	",
u8"gf (gf)	",
u8"gg (gg)	",
u8"ggee (ggee)	",
u8"gh (gh)	",
u8"gi (gi)	",
u8"gift (gift)	",
u8"gifts (gifts)	",
u8"gives (gives)	",
u8"giving (giving)	",
u8"gl (gl)	",
u8"glade (glade)	",
u8"glass (glass)	",
u8"gle (gle)	",
u8"global (global)	",
u8"globo (globo)	",
u8"gm (gm)	",
u8"gmail (gmail)	",
u8"gmbh (gmbh)	",
u8"gmo (gmo)	",
u8"gmx (gmx)	",
u8"gn (gn)	",
u8"godaddy (godaddy)	",
u8"gold (gold)	",
u8"goldpoint (goldpoint)	",
u8"golf (golf)	",
u8"goo (goo)	",
u8"goodhands (goodhands)	",
u8"goodyear (goodyear)	",
u8"goog (goog)	",
u8"google (google)	",
u8"gop (gop)	",
u8"got (got)	",
u8"gov (gov)	",
u8"gp (gp)	",
u8"gq (gq)	",
u8"gr (gr)	",
u8"grainger (grainger)	",
u8"graphics (graphics)	",
u8"gratis (gratis)	",
u8"green (green)	",
u8"gripe (gripe)	",
u8"grocery (grocery)	",
u8"group (group)	",
u8"gs (gs)	",
u8"gt (gt)	",
u8"gu (gu)	",
u8"guardian (guardian)	",
u8"gucci (gucci)	",
u8"guge (guge)	",
u8"guide (guide)	",
u8"guitars (guitars)	",
u8"guru (guru)	",
u8"gw (gw)	",
u8"gy (gy)	",
u8"hair (hair)	",
u8"hamburg (hamburg)	",
u8"hangout (hangout)	",
u8"haus (haus)	",
u8"hbo (hbo)	",
u8"hdfc (hdfc)	",
u8"hdfcbank (hdfcbank)	",
u8"health (health)	",
u8"healthcare (healthcare)	",
u8"help (help)	",
u8"helsinki (helsinki)	",
u8"here (here)	",
u8"hermes (hermes)	",
u8"hgtv (hgtv)	",
u8"hiphop (hiphop)	",
u8"hisamitsu (hisamitsu)	",
u8"hitachi (hitachi)	",
u8"hiv (hiv)	",
u8"hk (hk)	",
u8"hkt (hkt)	",
u8"hm (hm)	",
u8"hn (hn)	",
u8"hockey (hockey)	",
u8"holdings (holdings)	",
u8"holiday (holiday)	",
u8"homedepot (homedepot)	",
u8"homegoods (homegoods)	",
u8"homes (homes)	",
u8"homesense (homesense)	",
u8"honda (honda)	",
u8"honeywell (honeywell)	",
u8"horse (horse)	",
u8"hospital (hospital)	",
u8"host (host)	",
u8"hosting (hosting)	",
u8"hot (hot)	",
u8"hoteles (hoteles)	",
u8"hotels (hotels)	",
u8"hotmail (hotmail)	",
u8"house (house)	",
u8"how (how)	",
u8"hr (hr)	",
u8"hsbc (hsbc)	",
u8"ht (ht)	",
u8"hu (hu)	",
u8"hughes (hughes)	",
u8"hyatt (hyatt)	",
u8"hyundai (hyundai)	",
u8"ibm (ibm)	",
u8"icbc (icbc)	",
u8"ice (ice)	",
u8"icu (icu)	",
u8"id (id)	",
u8"ie (ie)	",
u8"ieee (ieee)	",
u8"ifm (ifm)	",
u8"ikano (ikano)	",
u8"il (il)	",
u8"im (im)	",
u8"imamat (imamat)	",
u8"imdb (imdb)	",
u8"immo (immo)	",
u8"immobilien (immobilien)	",
u8"in (in)	",
u8"industries (industries)	",
u8"infiniti (infiniti)	",
u8"info (info)	",
u8"ing (ing)	",
u8"ink (ink)	",
u8"institute (institute)	",
u8"insurance (insurance)	",
u8"insure (insure)	",
u8"int (int)	",
u8"intel (intel)	",
u8"international (international)	",
u8"intuit (intuit)	",
u8"investments (investments)	",
u8"io (io)	",
u8"ipiranga (ipiranga)	",
u8"iq (iq)	",
u8"ir (ir)	",
u8"irish (irish)	",
u8"is (is)	",
u8"iselect (iselect)	",
u8"ismaili (ismaili)	",
u8"ist (ist)	",
u8"istanbul (istanbul)	",
u8"it (it)	",
u8"itau (itau)	",
u8"itv (itv)	",
u8"iveco (iveco)	",
u8"iwc (iwc)	",
u8"jaguar (jaguar)	",
u8"java (java)	",
u8"jcb (jcb)	",
u8"jcp (jcp)	",
u8"je (je)	",
u8"jeep (jeep)	",
u8"jetzt (jetzt)	",
u8"jewelry (jewelry)	",
u8"jio (jio)	",
u8"jlc (jlc)	",
u8"jll (jll)	",
u8"jm (jm)	",
u8"jmp (jmp)	",
u8"jnj (jnj)	",
u8"jo (jo)	",
u8"jobs (jobs)	",
u8"joburg (joburg)	",
u8"jot (jot)	",
u8"joy (joy)	",
u8"jp (jp)	",
u8"jpmorgan (jpmorgan)	",
u8"jprs (jprs)	",
u8"juegos (juegos)	",
u8"juniper (juniper)	",
u8"kaufen (kaufen)	",
u8"kddi (kddi)	",
u8"ke (ke)	",
u8"kerryhotels (kerryhotels)	",
u8"kerrylogistics (kerrylogistics)	",
u8"kerryproperties (kerryproperties)	",
u8"kfh (kfh)	",
u8"kg (kg)	",
u8"kh (kh)	",
u8"ki (ki)	",
u8"kia (kia)	",
u8"kim (kim)	",
u8"kinder (kinder)	",
u8"kindle (kindle)	",
u8"kitchen (kitchen)	",
u8"kiwi (kiwi)	",
u8"km (km)	",
u8"kn (kn)	",
u8"koeln (koeln)	",
u8"komatsu (komatsu)	",
u8"kosher (kosher)	",
u8"kp (kp)	",
u8"kpmg (kpmg)	",
u8"kpn (kpn)	",
u8"kr (kr)	",
u8"krd (krd)	",
u8"kred (kred)	",
u8"kuokgroup (kuokgroup)	",
u8"kw (kw)	",
u8"ky (ky)	",
u8"kyoto (kyoto)	",
u8"kz (kz)	",
u8"la (la)	",
u8"lacaixa (lacaixa)	",
u8"ladbrokes (ladbrokes)	",
u8"lamborghini (lamborghini)	",
u8"lamer (lamer)	",
u8"lancaster (lancaster)	",
u8"lancia (lancia)	",
u8"lancome (lancome)	",
u8"land (land)	",
u8"landrover (landrover)	",
u8"lanxess (lanxess)	",
u8"lasalle (lasalle)	",
u8"lat (lat)	",
u8"latino (latino)	",
u8"latrobe (latrobe)	",
u8"law (law)	",
u8"lawyer (lawyer)	",
u8"lb (lb)	",
u8"lc (lc)	",
u8"lds (lds)	",
u8"lease (lease)	",
u8"leclerc (leclerc)	",
u8"lefrak (lefrak)	",
u8"legal (legal)	",
u8"lego (lego)	",
u8"lexus (lexus)	",
u8"lgbt (lgbt)	",
u8"li (li)	",
u8"liaison (liaison)	",
u8"lidl (lidl)	",
u8"life (life)	",
u8"lifeinsurance (lifeinsurance)	",
u8"lifestyle (lifestyle)	",
u8"lighting (lighting)	",
u8"like (like)	",
u8"lilly (lilly)	",
u8"limited (limited)	",
u8"limo (limo)	",
u8"lincoln (lincoln)	",
u8"linde (linde)	",
u8"link (link)	",
u8"lipsy (lipsy)	",
u8"live (live)	",
u8"living (living)	",
u8"lixil (lixil)	",
u8"lk (lk)	",
u8"llc (llc)	",
u8"loan (loan)	",
u8"loans (loans)	",
u8"locker (locker)	",
u8"locus (locus)	",
u8"loft (loft)	",
u8"lol (lol)	",
u8"london (london)	",
u8"lotte (lotte)	",
u8"lotto (lotto)	",
u8"love (love)	",
u8"lpl (lpl)	",
u8"lplfinancial (lplfinancial)	",
u8"lr (lr)	",
u8"ls (ls)	",
u8"lt (lt)	",
u8"ltd (ltd)	",
u8"ltda (ltda)	",
u8"lu (lu)	",
u8"lundbeck (lundbeck)	",
u8"lupin (lupin)	",
u8"luxe (luxe)	",
u8"luxury (luxury)	",
u8"lv (lv)	",
u8"ly (ly)	",
u8"ma (ma)	",
u8"macys (macys)	",
u8"madrid (madrid)	",
u8"maif (maif)	",
u8"maison (maison)	",
u8"makeup (makeup)	",
u8"man (man)	",
u8"management (management)	",
u8"mango (mango)	",
u8"map (map)	",
u8"market (market)	",
u8"marketing (marketing)	",
u8"markets (markets)	",
u8"marriott (marriott)	",
u8"marshalls (marshalls)	",
u8"maserati (maserati)	",
u8"mattel (mattel)	",
u8"mba (mba)	",
u8"mc (mc)	",
u8"mckinsey (mckinsey)	",
u8"md (md)	",
u8"me (me)	",
u8"med (med)	",
u8"media (media)	",
u8"meet (meet)	",
u8"melbourne (melbourne)	",
u8"meme (meme)	",
u8"memorial (memorial)	",
u8"men (men)	",
u8"menu (menu)	",
u8"meo (meo)	",
u8"merckmsd (merckmsd)	",
u8"metlife (metlife)	",
u8"mg (mg)	",
u8"mh (mh)	",
u8"miami (miami)	",
u8"microsoft (microsoft)	",
u8"mil (mil)	",
u8"mini (mini)	",
u8"mint (mint)	",
u8"mit (mit)	",
u8"mitsubishi (mitsubishi)	",
u8"mk (mk)	",
u8"ml (ml)	",
u8"mlb (mlb)	",
u8"mls (mls)	",
u8"mm (mm)	",
u8"mma (mma)	",
u8"mn (mn)	",
u8"mo (mo)	",
u8"mobi (mobi)	",
u8"mobile (mobile)	",
u8"mobily (mobily)	",
u8"moda (moda)	",
u8"moe (moe)	",
u8"moi (moi)	",
u8"mom (mom)	",
u8"monash (monash)	",
u8"money (money)	",
u8"monster (monster)	",
u8"mopar (mopar)	",
u8"mormon (mormon)	",
u8"mortgage (mortgage)	",
u8"moscow (moscow)	",
u8"moto (moto)	",
u8"motorcycles (motorcycles)	",
u8"mov (mov)	",
u8"movie (movie)	",
u8"movistar (movistar)	",
u8"mp (mp)	",
u8"mq (mq)	",
u8"mr (mr)	",
u8"ms (ms)	",
u8"msd (msd)	",
u8"mt (mt)	",
u8"mtn (mtn)	",
u8"mtr (mtr)	",
u8"mu (mu)	",
u8"museum (museum)	",
u8"mutual (mutual)	",
u8"mv (mv)	",
u8"mw (mw)	",
u8"mx (mx)	",
u8"my (my)	",
u8"mz (mz)	",
u8"na (na)	",
u8"nab (nab)	",
u8"nadex (nadex)	",
u8"nagoya (nagoya)	",
u8"name (name)	",
u8"nationwide (nationwide)	",
u8"natura (natura)	",
u8"navy (navy)	",
u8"nba (nba)	",
u8"nc (nc)	",
u8"ne (ne)	",
u8"nec (nec)	",
u8"net (net)	",
u8"netbank (netbank)	",
u8"netflix (netflix)	",
u8"network (network)	",
u8"neustar (neustar)	",
u8"new (new)	",
u8"newholland (newholland)	",
u8"news (news)	",
u8"next (next)	",
u8"nextdirect (nextdirect)	",
u8"nexus (nexus)	",
u8"nf (nf)	",
u8"nfl (nfl)	",
u8"ng (ng)	",
u8"ngo (ngo)	",
u8"nhk (nhk)	",
u8"ni (ni)	",
u8"nico (nico)	",
u8"nike (nike)	",
u8"nikon (nikon)	",
u8"ninja (ninja)	",
u8"nissan (nissan)	",
u8"nissay (nissay)	",
u8"nl (nl)	",
u8"no (no)	",
u8"nokia (nokia)	",
u8"northwesternmutual (northwesternmutual)	",
u8"norton (norton)	",
u8"now (now)	",
u8"nowruz (nowruz)	",
u8"nowtv (nowtv)	",
u8"np (np)	",
u8"nr (nr)	",
u8"nra (nra)	",
u8"nrw (nrw)	",
u8"ntt (ntt)	",
u8"nu (nu)	",
u8"nyc (nyc)	",
u8"nz (nz)	",
u8"obi (obi)	",
u8"observer (observer)	",
u8"off (off)	",
u8"office (office)	",
u8"okinawa (okinawa)	",
u8"olayan (olayan)	",
u8"olayangroup (olayangroup)	",
u8"oldnavy (oldnavy)	",
u8"ollo (ollo)	",
u8"om (om)	",
u8"omega (omega)	",
u8"one (one)	",
u8"ong (ong)	",
u8"onl (onl)	",
u8"online (online)	",
u8"onyourside (onyourside)	",
u8"ooo (ooo)	",
u8"open (open)	",
u8"oracle (oracle)	",
u8"orange (orange)	",
u8"org (org)	",
u8"organic (organic)	",
u8"origins (origins)	",
u8"osaka (osaka)	",
u8"otsuka (otsuka)	",
u8"ott (ott)	",
u8"ovh (ovh)	",
u8"pa (pa)	",
u8"page (page)	",
u8"panasonic (panasonic)	",
u8"panerai (panerai)	",
u8"paris (paris)	",
u8"pars (pars)	",
u8"partners (partners)	",
u8"parts (parts)	",
u8"party (party)	",
u8"passagens (passagens)	",
u8"pay (pay)	",
u8"pccw (pccw)	",
u8"pe (pe)	",
u8"pet (pet)	",
u8"pf (pf)	",
u8"pfizer (pfizer)	",
u8"pg (pg)	",
u8"ph (ph)	",
u8"pharmacy (pharmacy)	",
u8"phd (phd)	",
u8"philips (philips)	",
u8"phone (phone)	",
u8"photo (photo)	",
u8"photography (photography)	",
u8"photos (photos)	",
u8"physio (physio)	",
u8"piaget (piaget)	",
u8"pics (pics)	",
u8"pictet (pictet)	",
u8"pictures (pictures)	",
u8"pid (pid)	",
u8"pin (pin)	",
u8"ping (ping)	",
u8"pink (pink)	",
u8"pioneer (pioneer)	",
u8"pizza (pizza)	",
u8"pk (pk)	",
u8"pl (pl)	",
u8"place (place)	",
u8"play (play)	",
u8"playstation (playstation)	",
u8"plumbing (plumbing)	",
u8"plus (plus)	",
u8"pm (pm)	",
u8"pn (pn)	",
u8"pnc (pnc)	",
u8"pohl (pohl)	",
u8"poker (poker)	",
u8"politie (politie)	",
u8"porn (porn)	",
u8"post (post)	",
u8"pr (pr)	",
u8"pramerica (pramerica)	",
u8"praxi (praxi)	",
u8"press (press)	",
u8"prime (prime)	",
u8"pro (pro)	",
u8"prod (prod)	",
u8"productions (productions)	",
u8"prof (prof)	",
u8"progressive (progressive)	",
u8"promo (promo)	",
u8"properties (properties)	",
u8"property (property)	",
u8"protection (protection)	",
u8"pru (pru)	",
u8"prudential (prudential)	",
u8"ps (ps)	",
u8"pt (pt)	",
u8"pub (pub)	",
u8"pw (pw)	",
u8"pwc (pwc)	",
u8"py (py)	",
u8"qa (qa)	",
u8"qpon (qpon)	",
u8"quebec (quebec)	",
u8"quest (quest)	",
u8"qvc (qvc)	",
u8"racing (racing)	",
u8"radio (radio)	",
u8"raid (raid)	",
u8"re (re)	",
u8"read (read)	",
u8"realestate (realestate)	",
u8"realtor (realtor)	",
u8"realty (realty)	",
u8"recipes (recipes)	",
u8"red (red)	",
u8"redstone (redstone)	",
u8"redumbrella (redumbrella)	",
u8"rehab (rehab)	",
u8"reise (reise)	",
u8"reisen (reisen)	",
u8"reit (reit)	",
u8"reliance (reliance)	",
u8"ren (ren)	",
u8"rent (rent)	",
u8"rentals (rentals)	",
u8"repair (repair)	",
u8"report (report)	",
u8"republican (republican)	",
u8"rest (rest)	",
u8"restaurant (restaurant)	",
u8"review (review)	",
u8"reviews (reviews)	",
u8"rexroth (rexroth)	",
u8"rich (rich)	",
u8"richardli (richardli)	",
u8"ricoh (ricoh)	",
u8"rightathome (rightathome)	",
u8"ril (ril)	",
u8"rio (rio)	",
u8"rip (rip)	",
u8"rmit (rmit)	",
u8"ro (ro)	",
u8"rocher (rocher)	",
u8"rocks (rocks)	",
u8"rodeo (rodeo)	",
u8"rogers (rogers)	",
u8"room (room)	",
u8"rs (rs)	",
u8"rsvp (rsvp)	",
u8"ru (ru)	",
u8"rugby (rugby)	",
u8"ruhr (ruhr)	",
u8"run (run)	",
u8"rw (rw)	",
u8"rwe (rwe)	",
u8"ryukyu (ryukyu)	",
u8"sa (sa)	",
u8"saarland (saarland)	",
u8"safe (safe)	",
u8"safety (safety)	",
u8"sakura (sakura)	",
u8"sale (sale)	",
u8"salon (salon)	",
u8"samsclub (samsclub)	",
u8"samsung (samsung)	",
u8"sandvik (sandvik)	",
u8"sandvikcoromant (sandvikcoromant)	",
u8"sanofi (sanofi)	",
u8"sap (sap)	",
u8"sapo (sapo)	",
u8"sarl (sarl)	",
u8"sas (sas)	",
u8"save (save)	",
u8"saxo (saxo)	",
u8"sb (sb)	",
u8"sbi (sbi)	",
u8"sbs (sbs)	",
u8"sc (sc)	",
u8"sca (sca)	",
u8"scb (scb)	",
u8"schaeffler (schaeffler)	",
u8"schmidt (schmidt)	",
u8"scholarships (scholarships)	",
u8"school (school)	",
u8"schule (schule)	",
u8"schwarz (schwarz)	",
u8"science (science)	",
u8"scjohnson (scjohnson)	",
u8"scor (scor)	",
u8"scot (scot)	",
u8"sd (sd)	",
u8"se (se)	",
u8"search (search)	",
u8"seat (seat)	",
u8"secure (secure)	",
u8"security (security)	",
u8"seek (seek)	",
u8"select (select)	",
u8"sener (sener)	",
u8"services (services)	",
u8"ses (ses)	",
u8"seven (seven)	",
u8"sew (sew)	",
u8"sex (sex)	",
u8"sexy (sexy)	",
u8"sfr (sfr)	",
u8"sg (sg)	",
u8"sh (sh)	",
u8"shangrila (shangrila)	",
u8"sharp (sharp)	",
u8"shaw (shaw)	",
u8"shell (shell)	",
u8"shia (shia)	",
u8"shiksha (shiksha)	",
u8"shoes (shoes)	",
u8"shop (shop)	",
u8"shopping (shopping)	",
u8"shouji (shouji)	",
u8"show (show)	",
u8"showtime (showtime)	",
u8"shriram (shriram)	",
u8"si (si)	",
u8"silk (silk)	",
u8"sina (sina)	",
u8"singles (singles)	",
u8"site (site)	",
u8"sj (sj)	",
u8"sk (sk)	",
u8"ski (ski)	",
u8"skin (skin)	",
u8"sky (sky)	",
u8"skype (skype)	",
u8"sl (sl)	",
u8"sling (sling)	",
u8"sm (sm)	",
u8"smart (smart)	",
u8"smile (smile)	",
u8"sn (sn)	",
u8"sncf (sncf)	",
u8"so (so)	",
u8"soccer (soccer)	",
u8"social (social)	",
u8"softbank (softbank)	",
u8"software (software)	",
u8"sohu (sohu)	",
u8"solar (solar)	",
u8"solutions (solutions)	",
u8"song (song)	",
u8"sony (sony)	",
u8"soy (soy)	",
u8"space (space)	",
u8"spiegel (spiegel)	",
u8"sport (sport)	",
u8"spot (spot)	",
u8"spreadbetting (spreadbetting)	",
u8"sr (sr)	",
u8"srl (srl)	",
u8"srt (srt)	",
u8"st (st)	",
u8"stada (stada)	",
u8"staples (staples)	",
u8"star (star)	",
u8"starhub (starhub)	",
u8"statebank (statebank)	",
u8"statefarm (statefarm)	",
u8"statoil (statoil)	",
u8"stc (stc)	",
u8"stcgroup (stcgroup)	",
u8"stockholm (stockholm)	",
u8"storage (storage)	",
u8"store (store)	",
u8"stream (stream)	",
u8"studio (studio)	",
u8"study (study)	",
u8"style (style)	",
u8"su (su)	",
u8"sucks (sucks)	",
u8"supplies (supplies)	",
u8"supply (supply)	",
u8"support (support)	",
u8"surf (surf)	",
u8"surgery (surgery)	",
u8"suzuki (suzuki)	",
u8"sv (sv)	",
u8"swatch (swatch)	",
u8"swiftcover (swiftcover)	",
u8"swiss (swiss)	",
u8"sx (sx)	",
u8"sy (sy)	",
u8"sydney (sydney)	",
u8"symantec (symantec)	",
u8"systems (systems)	",
u8"sz (sz)	",
u8"tab (tab)	",
u8"taipei (taipei)	",
u8"talk (talk)	",
u8"taobao (taobao)	",
u8"target (target)	",
u8"tatamotors (tatamotors)	",
u8"tatar (tatar)	",
u8"tattoo (tattoo)	",
u8"tax (tax)	",
u8"taxi (taxi)	",
u8"tc (tc)	",
u8"tci (tci)	",
u8"td (td)	",
u8"tdk (tdk)	",
u8"team (team)	",
u8"tech (tech)	",
u8"technology (technology)	",
u8"tel (tel)	",
u8"telecity (telecity)	",
u8"telefonica (telefonica)	",
u8"temasek (temasek)	",
u8"tennis (tennis)	",
u8"teva (teva)	",
u8"tf (tf)	",
u8"tg (tg)	",
u8"th (th)	",
u8"thd (thd)	",
u8"theater (theater)	",
u8"theatre (theatre)	",
u8"tiaa (tiaa)	",
u8"tickets (tickets)	",
u8"tienda (tienda)	",
u8"tiffany (tiffany)	",
u8"tips (tips)	",
u8"tires (tires)	",
u8"tirol (tirol)	",
u8"tj (tj)	",
u8"tjmaxx (tjmaxx)	",
u8"tjx (tjx)	",
u8"tk (tk)	",
u8"tkmaxx (tkmaxx)	",
u8"tl (tl)	",
u8"tm (tm)	",
u8"tmall (tmall)	",
u8"tn (tn)	",
u8"to (to)	",
u8"today (today)	",
u8"tokyo (tokyo)	",
u8"tools (tools)	",
u8"top (top)	",
u8"toray (toray)	",
u8"toshiba (toshiba)	",
u8"total (total)	",
u8"tours (tours)	",
u8"town (town)	",
u8"toyota (toyota)	",
u8"toys (toys)	",
u8"tr (tr)	",
u8"trade (trade)	",
u8"trading (trading)	",
u8"training (training)	",
u8"travel (travel)	",
u8"travelchannel (travelchannel)	",
u8"travelers (travelers)	",
u8"travelersinsurance (travelersinsurance)	",
u8"trust (trust)	",
u8"trv (trv)	",
u8"tt (tt)	",
u8"tube (tube)	",
u8"tui (tui)	",
u8"tunes (tunes)	",
u8"tushu (tushu)	",
u8"tv (tv)	",
u8"tvs (tvs)	",
u8"tw (tw)	",
u8"tz (tz)	",
u8"ua (ua)	",
u8"ubank (ubank)	",
u8"ubs (ubs)	",
u8"uconnect (uconnect)	",
u8"ug (ug)	",
u8"uk (uk)	",
u8"unicom (unicom)	",
u8"university (university)	",
u8"uno (uno)	",
u8"uol (uol)	",
u8"ups (ups)	",
u8"us (us)	",
u8"uy (uy)	",
u8"uz (uz)	",
u8"va (va)	",
u8"vacations (vacations)	",
u8"vana (vana)	",
u8"vanguard (vanguard)	",
u8"vc (vc)	",
u8"ve (ve)	",
u8"vegas (vegas)	",
u8"ventures (ventures)	",
u8"verisign (verisign)	",
u8"versicherung (versicherung)	",
u8"vet (vet)	",
u8"vg (vg)	",
u8"vi (vi)	",
u8"viajes (viajes)	",
u8"video (video)	",
u8"vig (vig)	",
u8"viking (viking)	",
u8"villas (villas)	",
u8"vin (vin)	",
u8"vip (vip)	",
u8"virgin (virgin)	",
u8"visa (visa)	",
u8"vision (vision)	",
u8"vista (vista)	",
u8"vistaprint (vistaprint)	",
u8"viva (viva)	",
u8"vivo (vivo)	",
u8"vlaanderen (vlaanderen)	",
u8"vn (vn)	",
u8"vodka (vodka)	",
u8"volkswagen (volkswagen)	",
u8"volvo (volvo)	",
u8"vote (vote)	",
u8"voting (voting)	",
u8"voto (voto)	",
u8"voyage (voyage)	",
u8"vu (vu)	",
u8"vuelos (vuelos)	",
u8"wales (wales)	",
u8"walmart (walmart)	",
u8"walter (walter)	",
u8"wang (wang)	",
u8"wanggou (wanggou)	",
u8"warman (warman)	",
u8"watch (watch)	",
u8"watches (watches)	",
u8"weather (weather)	",
u8"weatherchannel (weatherchannel)	",
u8"webcam (webcam)	",
u8"weber (weber)	",
u8"website (website)	",
u8"wed (wed)	",
u8"wedding (wedding)	",
u8"weibo (weibo)	",
u8"weir (weir)	",
u8"wf (wf)	",
u8"whoswho (whoswho)	",
u8"wien (wien)	",
u8"wiki (wiki)	",
u8"williamhill (williamhill)	",
u8"win (win)	",
u8"windows (windows)	",
u8"wine (wine)	",
u8"winners (winners)	",
u8"wme (wme)	",
u8"wolterskluwer (wolterskluwer)	",
u8"woodside (woodside)	",
u8"work (work)	",
u8"works (works)	",
u8"world (world)	",
u8"wow (wow)	",
u8"ws (ws)	",
u8"wtc (wtc)	",
u8"wtf (wtf)	",
u8"xbox (xbox)	",
u8"xerox (xerox)	",
u8"xfinity (xfinity)	",
u8"xihuan (xihuan)	",
u8"xin (xin)	",
u8"कॉम (xn--11b4c3d)	",
u8"セール (xn--1ck2e1b)	",
u8"佛山 (xn--1qqw23a)	",
u8"ಭಾರತ (xn--2scrj9c)	",
u8"慈善 (xn--30rr7y)	",
u8"集团 (xn--3bst00m)	",
u8"在线 (xn--3ds443g)	",
u8"한국 (xn--3e0b707e)	",
u8"ଭାରତ (xn--3hcrj9c)	",
u8"大众汽车 (xn--3oq18vl8pn36a)	",
u8"点看 (xn--3pxu8k)	",
u8"คอม (xn--42c2d9a)	",
u8"ভাৰত (xn--45br5cyl)	",
u8"ভারত (xn--45brj9c)	",
u8"八卦 (xn--45q11c)	",
u8"موقع (xn--4gbrim)	",
u8"বাংলা (xn--54b7fta0cc)	",
u8"公益 (xn--55qw42g)	",
u8"公司 (xn--55qx5d)	",
u8"香格里拉 (xn--5su34j936bgsg)	",
u8"网站 (xn--5tzm5g)	",
u8"移动 (xn--6frz82g)	",
u8"我爱你 (xn--6qq986b3xl)	",
u8"москва (xn--80adxhks)	",
u8"қаз (xn--80ao21a)	",
u8"католик (xn--80aqecdr1a)	",
u8"онлайн (xn--80asehdb)	",
u8"сайт (xn--80aswg)	",
u8"联通 (xn--8y0a063a)	",
u8"срб (xn--90a3ac)	",
u8"бг (xn--90ae)	",
u8"бел (xn--90ais)	",
u8"קום (xn--9dbq2a)	",
u8"时尚 (xn--9et52u)	",
u8"微博 (xn--9krt00a)	",
u8"淡马锡 (xn--b4w605ferd)	",
u8"ファッション (xn--bck1b9a5dre4c)	",
u8"орг (xn--c1avg)	",
u8"नेट (xn--c2br7g)	",
u8"ストア (xn--cck2b3b)	",
u8"삼성 (xn--cg4bki)	",
u8"சிங்கப்பூர் (xn--clchc0ea0b2g2a9gcd)	",
u8"商标 (xn--czr694b)	",
u8"商店 (xn--czrs0t)	",
u8"商城 (xn--czru2d)	",
u8"дети (xn--d1acj3b)	",
u8"мкд (xn--d1alf)	",
u8"ею (xn--e1a4c)	",
u8"ポイント (xn--eckvdtc9d)	",
u8"新闻 (xn--efvy88h)	",
u8"工行 (xn--estv75g)	",
u8"家電 (xn--fct429k)	",
u8"كوم (xn--fhbei)	",
u8"中文网 (xn--fiq228c5hs)	",
u8"中信 (xn--fiq64b)	",
u8"中国 (xn--fiqs8s)	",
u8"中國 (xn--fiqz9s)	",
u8"娱乐 (xn--fjq720a)	",
u8"谷歌 (xn--flw351e)	",
u8"భారత్ (xn--fpcrj9c3d)	",
u8"ලංකා (xn--fzc2c9e2c)	",
u8"電訊盈科 (xn--fzys8d69uvgm)	",
u8"购物 (xn--g2xx48c)	",
u8"クラウド (xn--gckr3f0f)	",
u8"ભારત (xn--gecrj9c)	",
u8"通販 (xn--gk3at1e)	",
u8"भारतम् (xn--h2breg3eve)	",
u8"भारत (xn--h2brj9c)	",
u8"भारोत (xn--h2brj9c8c)	",
u8"网店 (xn--hxt814e)	",
u8"संगठन (xn--i1b6b1a6a2e)	",
u8"餐厅 (xn--imr513n)	",
u8"网络 (xn--io0a7i)	",
u8"ком (xn--j1aef)	",
u8"укр (xn--j1amh)	",
u8"香港 (xn--j6w193g)	",
u8"诺基亚 (xn--jlq61u9w7b)	",
u8"食品 (xn--jvr189m)	",
u8"飞利浦 (xn--kcrx77d1x4a)	",
u8"台湾 (xn--kprw13d)	",
u8"台灣 (xn--kpry57d)	",
u8"手表 (xn--kpu716f)	",
u8"手机 (xn--kput3i)	",
u8"мон (xn--l1acc)	",
u8"الجزائر (xn--lgbbat1ad8j)	",
u8"عمان (xn--mgb9awbf)	",
u8"ارامكو (xn--mgba3a3ejt)	",
u8"ایران (xn--mgba3a4f16a)	",
u8"العليان (xn--mgba7c0bbn0a)	",
u8"اتصالات (xn--mgbaakc7dvf)	",
u8"امارات (xn--mgbaam7a8h)	",
u8"بازار (xn--mgbab2bd)	",
u8"پاکستان (xn--mgbai9azgqp6j)	",
u8"الاردن (xn--mgbayh7gpa)	",
u8"موبايلي (xn--mgbb9fbpob)	",
u8"بارت (xn--mgbbh1a)	",
u8"بھارت (xn--mgbbh1a71e)	",
u8"المغرب (xn--mgbc0a9azcg)	",
u8"ابوظبي (xn--mgbca7dzdo)	",
u8"السعودية (xn--mgberp4a5d4ar)	",
u8"ڀارت (xn--mgbgu82a)	",
u8"كاثوليك (xn--mgbi4ecexp)	",
u8"سودان (xn--mgbpl2fh)	",
u8"همراه (xn--mgbt3dhd)	",
u8"عراق (xn--mgbtx2b)	",
u8"مليسيا (xn--mgbx4cd0ab)	",
u8"澳門 (xn--mix891f)	",
u8"닷컴 (xn--mk1bu44c)	",
u8"政府 (xn--mxtq1m)	",
u8"شبكة (xn--ngbc5azd)	",
u8"بيتك (xn--ngbe9e0a)	",
u8"عرب (xn--ngbrx)	",
u8"გე (xn--node)	",
u8"机构 (xn--nqv7f)	",
u8"组织机构 (xn--nqv7fs00ema)	",
u8"健康 (xn--nyqy26a)	",
u8"ไทย (xn--o3cw4h)	",
u8"سورية (xn--ogbpf8fl)	",
u8"招聘 (xn--otu796d)	",
u8"рус (xn--p1acf)	",
u8"рф (xn--p1ai)	",
u8"珠宝 (xn--pbt977c)	",
u8"تونس (xn--pgbs0dh)	",
u8"大拿 (xn--pssy2u)	",
u8"みんな (xn--q9jyb4c)	",
u8"グーグル (xn--qcka1pmc)	",
u8"ελ (xn--qxam)	",
u8"世界 (xn--rhqv96g)	",
u8"書籍 (xn--rovu88b)	",
u8"ഭാരതം (xn--rvc1e0am3e)	",
u8"ਭਾਰਤ (xn--s9brj9c)	",
u8"网址 (xn--ses554g)	",
u8"닷넷 (xn--t60b56a)	",
u8"コム (xn--tckwe)	",
u8"天主教 (xn--tiq49xqyj)	",
u8"游戏 (xn--unup4y)	",
u8"vermögensberater (xn--vermgensberater-ctb)	",
u8"vermögensberatung (xn--vermgensberatung-pwb)	",
u8"企业 (xn--vhquv)	",
u8"信息 (xn--vuq861b)	",
u8"嘉里大酒店 (xn--w4r85el8fhu5dnra)	",
u8"嘉里 (xn--w4rs40l)	",
u8"مصر (xn--wgbh1c)	",
u8"قطر (xn--wgbl6a)	",
u8"广东 (xn--xhq521b)	",
u8"இலங்கை (xn--xkc2al3hye2a)	",
u8"இந்தியா (xn--xkc2dl3a5ee0h)	",
u8"հայ (xn--y9a3aq)	",
u8"新加坡 (xn--yfro4i67o)	",
u8"فلسطين (xn--ygbi2ammx)	",
u8"政务 (xn--zfr164b)	",
u8"xperia (xperia)	",
u8"xxx (xxx)	",
u8"xyz (xyz)	",
u8"yachts (yachts)	",
u8"yahoo (yahoo)	",
u8"yamaxun (yamaxun)	",
u8"yandex (yandex)	",
u8"ye (ye)	",
u8"yodobashi (yodobashi)	",
u8"yoga (yoga)	",
u8"yokohama (yokohama)	",
u8"you (you)	",
u8"youtube (youtube)	",
u8"yt (yt)	",
u8"yun (yun)	",
u8"za (za)	",
u8"zappos (zappos)	",
u8"zara (zara)	",
u8"zero (zero)	",
u8"zip (zip)	",
u8"zippo (zippo)	",
u8"zm (zm)	",
u8"zone (zone)	",
u8"zuerich (zuerich)	",
u8"zw (zw)	",
nullptr,
};