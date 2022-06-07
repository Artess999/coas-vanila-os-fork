// boal 08/04/06 общий диалог верфи
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
			DialogExit();
			NextDiag.CurrentNode = "Master_Ship";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги приятель, пока солдаты не сделали из тебя решето..."),
					LinkRandPhrase("Что тебе нужно, негодяй?! Городская стража уже взяла твой след, далеко тебе не уйти, грязный пират!", "Грязный убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзавец! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			NextDiag.TempNode = "First time";

			//homo Линейка Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase("Эй, доктор Блад! " + TimeGreeting() + ".",
                                    "Рад видеть Вас, Питер Блад.",
                                    "Хорошо, что Вы заглянули ко мне, " + GetFullName(pchar) + ". Как поживает полковник Бишоп?");
                Link.l1 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l1.go = "exit";
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.ShipForJack") && Pchar.questTemp.CapBloodLine.ShipForJack == true)
                {
                    Link.l2 = "Я ищу капитана, который доставит моего друга на Тортугу за умеренную плату в три тысячи пиастров. Нет ли у Вас кого-то на примете?";
    				Link.l2.go = "Blood_Shipyard1";
                }
				break;
            }

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = TimeGreeting() + "! Я "+ GetFullName(NPChar) + ", владелец этой верфи.";
				Link.l1 = "Рад знакомству. Я капитан " + GetFullName(Pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				//--->> квест украсть чертеж на верфи
				//дача квеста
				if (rand(1) && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questShipyardsMap") > 7 && !CheckAttribute(pchar, "questTemp.different.ShipyardsMap"))
				{
					dialog.text = "Послушайте, у меня есть к вам одно важное дело. Надеюсь, сумеете мне помочь...";
					link.l1 = "Давайте послушаем, что за дело.";
					link.l1.go = "ShipyardsMap_1";
					SaveCurrentNpcQuestDateParam(npchar, "questShipyardsMap");
					break;
				}
				//<<--- квест украсть чертеж на верфи

				dialog.Text = pcharrepphrase("А, это опять ты? Ну да ладно, деньги не пахнут.",
                                        TimeGreeting() + ", чем я могу помочь вам, " + GetAddress_Form(NPChar) + "?");
				Link.l1 = pcharrepphrase("Вот-вот, я плачу - ты делаешь.",
                                        "Нужно воспользоваться услугами верфи.");
				Link.l1.go = "Shipyard";
				link.l11 = "Мне нужны орудия на корабль.";
			    link.l11.go = "Cannons";
				Link.l2 = "Я только хочу поговорить.";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Я хотел бы поговорить с вами о делах финансовых.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".",
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я должен кое-что забрать...");
					link.l7.go = "IntelligenceForAll";
				}
				//--> квест Аззи.
	    		if (CheckCharacterItem(pchar, "Azzy_bottle"))
	            {
	                link.l5 = "Слушай, у меня есть одна штука - жестянка. Мне нужно аккуратненько ее вскрыть. Сможешь сделать это? Я заплачу.";
	                if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
	                {
	                    link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
	                }
	                else
	                {
	                    link.l5.go = "AzzyTryTalk";
	                }
	            }
	            //<-- на квест Аззи.
				//проверка выполнения квеста украсть чертеж на верфи
				if (CheckCharacterItem(pchar, "ShipyardsMap") && CheckAttribute(pchar, "questTemp.different.ShipyardsMap.Id") && pchar.questTemp.different.ShipyardsMap.Id == npchar.id)
				{
					link.l6 = "Я выполнил ваше поручение. Чертеж из верфи " + XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Gen") + " у меня.";
					link.l6.go = "ShipyardsMapOk_1";
				}
				Link.l9 = "Мне нужно идти.";
				Link.l9.go = "exit";
			}
		break;

		case "Meeting":
				dialog.Text = "Хорошо, я рад встречи с новым клиентом. Моя верфь к вашим услугам.";
				Link.l1 = "Великолепно, " + GetFullName(NPChar) + ". Давайте посмотрим то, что вы можете мне предложить.";
				Link.l1.go = "Shipyard";
				link.l11 = "Мне нужны орудия на корабль.";
				link.l11.go = "Cannons";
				Link.l2 = "Я только хочу поговорить.";
				Link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Я хотел бы поговорить с вами о делах финансовых.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".",
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я должен кое-что забрать...");
					link.l7.go = "IntelligenceForAll";
				}
				//--> квест Аззи.
	    		if (CheckCharacterItem(pchar, "Azzy_bottle"))
	            {
	                link.l5 = "Слушай, у меня есть одна штука - жестянка. Мне нужно аккуратненько ее вскрыть. Сможешь сделать это? Я заплачу.";
	                if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
	                {
	                    link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
	                }
	                else
	                {
	                    link.l5.go = "AzzyTryTalk";
	                }
	            }
	            //<-- на квест Аззи.
				Link.l9 = "Я должен идти. Благодарю вас.";
				Link.l9.go = "exit";
		break;

		case "shipyard":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
													                 "Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, еще увидимся!",
				                                                 "Я не хотел вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Нет. Мой корабль называется Black Perl. Что это ты побелел? Ха-ха! Шутка!",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";
			}
		break;

		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
													                 "Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, еще увидимся!",
				                                                 "Я не хотел вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Нет. Мой корабль называется Black Perl. Что это ты побелел? Ха-ха! Шутка!",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";
			}
		break;
		// квест украсть чертеж на верфи
		case "ShipyardsMap_1":
			dialog.text = "Мне нужно раздобыть один важный чертеж. Очень важный чертеж...";
			link.l1 = "Хм. Что за чертеж и где его взять?";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			pchar.questTemp.different = "ShipyardsMap";
			pchar.questTemp.different.ShipyardsMap = "toTarget";
			pchar.questTemp.different.ShipyardsMap.Id = npchar.id; //квестодатель
			pchar.questTemp.different.ShipyardsMap.city = findShipyardCity(npchar);
			pchar.questTemp.different.ShipyardsMap.what = LinkRandPhrase("корвета", "флейта", "фрегата");
			pchar.questTemp.different.ShipyardsMap.chance = rand(5); //ценность чертежа
			if (rand(12) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				pchar.questTemp.different.ShipyardsMap.skladFight = false; //не будет драки на складе
			}
			else
			{
				pchar.questTemp.different.ShipyardsMap.skladFight = true; //будет драка на складе
			}
			pchar.questTemp.different.ShipyardsMap.sklad = rand(3)+1; //сколько денег попросят на складе за открытие двери
			pchar.questTemp.different.ShipyardsMap.fightQty = 2 + rand(3); //количество бойцов на верфи
			dialog.text = "Мне стало известно, что на верфи " + XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Gen") + " ведется постройка новейшего " + pchar.questTemp.different.ShipyardsMap.what + ". Мне нужен чертеж, по которым ведутся работы.";
			link.l1 = "И что я должен сделать?";
			link.l1.go = "ShipyardsMap_3";
		break;
		case "ShipyardsMap_3":
			dialog.text = "Привезти его мне. Проблема заключается в том, что чертеж, ввиду его ценности, постоянно находится на виду у хозяина верфи. А если быть точным - на его столе.";
			link.l1 = "И что вы предлагаете?";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Хм, я предлагаю доставить чертеж мне. Как вы это сделаете - ваши проблемы. За эту работу я готов щедро заплатить, хотя многое будет зависеть от действительной ценности заложенной в чертеже информации.";
			link.l1 = "Как это понять?";
			link.l1.go = "ShipyardsMap_5";
		break;
		case "ShipyardsMap_5":
			dialog.text = "Если проект имеет новые технологические решения, о которых мне неизвестно, то сумма будет достаточно велика. В обратном случае размер гонорара будет невысок... Ну что, вы согласны взяться за это дело?";
			link.l1 = "Нет, мне это неинтересно. Доставка 'кота в мешке' кажется мне неблагодарной работой.";
			link.l1.go = "ShipyardsMap_disagree";
			link.l2 = "Думаю, мне стоит этим заняться. Берусь!";
			link.l2.go = "ShipyardsMap_agree";
		break;

		case "ShipyardsMap_disagree":
			dialog.text = "Хм, ну что же, очень жаль.";
			link.l1 = "Мне тоже...";
			link.l1.go = "exit";
			pchar.questTemp.different = "free";
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
		break;
		case "ShipyardsMap_agree":
			dialog.text = "Ну что же, тогда удачи вам. Я буду ждать вас с результатами. В сроках вы никак не ограничены.";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
			sld = ItemsFromID("ShipyardsMap");
			sld.shown = true;
			sld.startLocation = pchar.questTemp.different.ShipyardsMap.city + "_Shipyard";
			sld.startLocator = "item1";
			sld.ShipName = pchar.questTemp.different.ShipyardsMap.what;
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			ReOpenQuestHeader("ShipyardsMap");
			AddQuestRecord("ShipyardsMap", "1");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("ShipyardsMap", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Dat"));
			AddQuestUserData("ShipyardsMap", "sShip", pchar.questTemp.different.ShipyardsMap.what);
		break;

		case "Allarm":
			dialog.text = "Ах ты паршивец! Ты что же это делаешь?! Ну, держись, проучу тебя как следует. А ну, ребята, хватайте топоры!";
			link.l1 = "Топоры?..";
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			AddCharacterExpToSkill(pchar, "FencingLight", 10);
			AddCharacterExpToSkill(pchar, "Fencing", 10);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 10);
			ChangeCharacterReputation(pchar, -1);
			for (i=1; i<=sti(pchar.questTemp.different.ShipyardsMap.fightQty); i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("shipowner_"+i, "shipowner_"+(rand(15)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
				FantomMakeCoolFighter(sld, iTemp, 70, 70, "topor"+(rand(2)+1), "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;

		case "Allarm_1":
			dialog.text = "Ты что, угрожать мне вздумал?! А ну, ребята, хватайте топоры!";
			link.l1 = "Топоры?..";
			link.l1.go = "fight";
			ChangeCharacterReputation(pchar, -1);
			for (i=1; i<=5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("shipowner_"+i, "shipowner_"+(rand(15)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
				FantomMakeCoolFighter(sld, iTemp, 70, 70, "topor"+(rand(2)+1), "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;

		case "ShipyardsMapOk_1":
			sTemp = pchar.questTemp.different.ShipyardsMap.what;
			dialog.text = "Отлично! Ну, давайте посмотрим, что же это за хваленый " + strcut(sTemp, 0, strlen(sTemp)-2) + "...";
			link.l1 = "Смотрите.";
			link.l1.go = "ShipyardsMapOk_2";
		break;
		case "ShipyardsMapOk_2":
			TakeItemFromCharacter(pchar, "ShipyardsMap");
			if (sti(pchar.questTemp.different.ShipyardsMap.chance) > 0)
			{
				dialog.text = "Да, это чертеж имеет определенную ценность. Я готов заплатить вам за него " + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.chance)*1000) + ".";
				link.l1 = "Прекрасно!";
				link.l1.go = "ShipyardsMapOk_5";
			}
			else
			{
				dialog.text = "Так-так... Хм, вынужден вас огорчить. Ничего полезного я для себя не вижу. Вы, кажется, вообще не то прихватили.";
				link.l1 = "Вы заказывали то, что лежало на столе. Именно это я вам и принес. Я же не разбираюсь в этих чертежах!";
				link.l1.go = "ShipyardsMapOk_3";
			}
		break;

		case "ShipyardsMapOk_3":
			dialog.text = "Увы, за это я вообще ничего не могу заплатить. Извините, но эта бумага мне не нужна.";
			link.l1 = "Хм, я не считаю ваш поступок честным, но дебошей устраивать не буду.";
			link.l1.go = "ShipyardsMapOk_4";
			link.l2 = "Отдавай мои деньги! Иначе пущу кровь!";
			link.l2.go = "Allarm_1";
		break;
		case "ShipyardsMapOk_4":
			dialog.text = "Поймите меня правильно, вы могли спокойно взять это где-нибудь на свалке. Этот чертеж ничего не стоит.";
			link.l1 = "Я вас понял...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
			AddQuestRecord("ShipyardsMap", "3");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("ShipyardsMap");
		break;

		case "ShipyardsMapOk_5":
			dialog.text = "Извольте получить. Спасибо вам за проделанную работу.";
			link.l1 = "Да не за что...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			ChangeCharacterReputation(pchar, 5);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.ShipyardsMap.chance)*1000);
			AddQuestRecord("ShipyardsMap", "4");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("ShipyardsMap", "iMoney", sti(pchar.questTemp.different.ShipyardsMap.chance)*1000);
			CloseQuestHeader("ShipyardsMap");
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
		break;

        ////////////////////////////////////////////////homo линейка Блада/////////////////////////////////////////
        case "Blood_Shipyard1":
			dialog.text = "Кхм, ну, это зависит от того, кто ваш друг и зачем ему нужно на Тортугу, доктор.";
			link.l1 = "Этот... мой друг, он - честный торговец... хм, скупщик всякого старья.";
			link.l1.go = "Blood_Shipyard2";
			link.l2 = "Мой дорогой друг - флибустьер, давеча потерявший свое судно при атаке на испанский патруль.";
			link.l2.go = "Blood_Shipyard3";
			link.l3 = "Вы о нем слышали. Капитан Жак Соловей.";
			link.l3.go = "Blood_Shipyard4";
		break;

		case "Blood_Shipyard2":
			dialog.text = "Скупщик? Торговец-скупщик хочет попасть на Тортугу? Вы меня разыгрываете, доктор!..";
			link.l1 = "И в мыслях не было, сэр! Я всего лишь, кхм, пытаюсь помочь. Ну, ему. Другу. Да.";
			link.l1.go = "Blood_Shipyard5";

		break;
		case "Blood_Shipyard3":
			dialog.text = "И где же это случилось?";
			link.l1 = "Это было... эхх, якорь мне в ...! Забудь.";
			link.l1.go = "exit";
			CloseQuestHeader("PirateQuest");
			Pchar.questTemp.CapBloodLine.ShipForJack = false;

		break;
        case "Blood_Shipyard4":
			dialog.text = "Вы хотите сказать, бывший капитан... мм?";
			link.l1 = "Эээ... ну, да... бывший. Вы его знаете?";
			link.l1.go = "Blood_Shipyard6";
		break;

        case "Blood_Shipyard5":
			dialog.text = "Что ж, я вам поверю. На этот раз. Где-то в городе находится человек по имени Джон Майнер. Поговорите с ним, он только что купил у меня корвет.";
			link.l1 = "Премного благодарен. ";
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "2");
		break;

        case "Blood_Shipyard6":
			dialog.text = "Как вы правильно подметили, я о нем слышал. Не знаю, как жил Жак Соловей до того, как отправился с Тортуги за кладом на... это было в то время, когда он был капитаном ''Эбеновой Устрицы''.";
			link.l1 = "Что?! Он не упоминал об этом.";
			link.l1.go = "Blood_Shipyard7";
		break;

        case "Blood_Shipyard7":
			dialog.text = "Теперь он не распускает язык - жизнь его проучила. На третий день пути пришел к нему старпом и говорит: ''у нас уговор делиться''. Мол, все должны знать, где сокровища. Ну, Жак дал ему карту, и ночью...";
			link.l1 = "...был бунт?";
			link.l1.go = "Blood_Shipyard8";
		break;

        case "Blood_Shipyard8":
			dialog.text = "Нет! Не перебивай меня! Ночью карта пропала. Морские волки обнаружили, что табака полно, а трубок нет вовсе, и дружно карту сокровищ скурили, пустив на самокрутки. Наутро четвертого дня ром кончился, табак тоже, а сокровищ и вовсе теперь не найти. Какой-то барбос обвинил во всем Жака, и команда поддержала. Пираты высадили его на остров, чтобы он подох… после того как сбрендит от жары. Знаешь, Питер, когда пирата гонят, ему дают пистолет с одной пулей. Всего одной. Ну, для охоты или чтобы спастись маловато, но… Соловью ни черта не дали. Но Жак выбрался с острова, а злобу хранит по сей день. Вот уже десять лет он не может придумать способ, как отомстить новому капитану ''Устрицы'' эпично и зрелищно...";
			link.l1 = "История потрясающая, но что насчет капитана и корабля? Порекомендуете кого-нибудь?";
			link.l1.go = "Blood_Shipyard9";
			link.l2 = "А как Жак выбрался?";
			link.l2.go = "Blood_Shipyard10";
		break;

        case "Blood_Shipyard9":
			dialog.text = "Найди человека по имени Джон Майнер - он где-то в городе. Думаю, на только что приобретенном корвете он отправится именно на Тортугу.";
			link.l1 = "Премного благодарен. ";
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "2");
		break;

        case "Blood_Shipyard10":
			dialog.text = "О-о, расскажу! Он оказался на отмели и просидел там три дня и три ночи… чтобы обитающая там живность, хмм, немного к нему привыкла. Наутро четвертого дня он схватил двух морских черепах, связал и от души над ними поржал!..";
			link.l1 = "М-м... а выбрался-то как?";
			link.l1.go = "Blood_Shipyard11";
		break;

        case "Blood_Shipyard11":
			dialog.text = "Просидев три дня, он еще сутки ржал над черепахами, а потом приплыли контрабандисты, у которых там тайник, и тоже поржали искренне, после чего, в обмен на связанных черепах, взяли его с собой.";
			link.l1 = "Невероятно! Так как мне помочь ему добраться до Тортуги?";
			link.l1.go = "Blood_Shipyard12";
		break;

        case "Blood_Shipyard12":
			dialog.text = "Тебе нужен капитан Майнер, Джон Майнер - он только что приобрел у меня корвет. Отплыть он пока не успел, так что поищи его в городе.";
			link.l1 = "Премного благодарен.";
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "3");
		break;

	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}
