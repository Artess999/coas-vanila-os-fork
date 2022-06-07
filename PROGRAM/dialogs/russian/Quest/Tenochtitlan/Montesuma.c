
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "О-о-о, еще один белый пожаловал. С чем ты пришел к Теночтитлану?";
			link.l1 = "Посмотреть что к чему. Такой я человек - хочу все знать.";
			link.l1.go = "FT_1";
			if (pchar.questTemp.Teno == "takeFire")
			{
				dialog.text = "Здраствуй, белый человек. Зачем ты пришел в Теночтитлан?";
				link.l1 = "Посмотреть что к чему. Такой я человек - хочу все знать. Я так понимаю, что ты ацтек, приятель.";
				link.l1.go = "FTS_1";
			}
		break;
		case "FT_1":
			dialog.text = "Понятно... Но ты хоть знаешь, куда ты попал?";
			link.l1 = "Я знаю, что этот город - индейская столица. И что сам Кортес прошелся здесь огнем и мечом.";
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = "Да, это так. Этот город имеет имя Теночтитлан, а людей, что жили здесь на протяжении веков, звали ацтеками.";
			link.l1 = "Ясно. И ты тоже ацтек, как я понимаю?";
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = "Да, я ацтек, ты угадал. Меня зовут Монтесума. А как я могу называть тебя?";
			link.l1 = "Меня зовут капитан " + GetFullName(pchar) + ". Монтесума... Кажется, так звали индейского вождя.";
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = "Я назван в его честь\nСкажи мне, белый капитан " + GetFullName(pchar) + ", что ты собираешься делать дальше?";
			link.l1 = "Хочу проникнуть в город.";
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = "Наверное, ты понял, что сделать это не так просто. Дамба к городу надежно защищена заклятием огня. Совсем недавно здесь было много белых людей. Все они сгорели...";
			link.l1 = "Ну, не все. Насколько мне известно, кое-кому ты раскроил череп.";
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = "Это так, но они сами виноваты в своей смерти. Не надо было трогать Монтесуму.";
			link.l1 = "Ладно, не будем об этом. Расскажи-ка мне лучше, что там в городе есть интересного? Там живет кто-то, или нет? И ты что тут делаешь, на этом побережье?";
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = "О-о, это долгая история. Приготовься слушать, белый капитан.\n"+
				"Мои предки пришли на берега этого озера, называемого Тескоко, много веков назад. Тогда их звали мешики. Берега озера были заселены другими племенами, которые враждебно отнеслись к пришельцам. Но наш верховный бог, Уицилопочтли, повелел им остаться здесь. Тогда вождь мешиков Теноч принял решение остаться на берегах Тескоко, а мешики стали называться теночками.\n"+
				"Кошкоштли, вождь могущественного города Кулуакана, замыслил истребить теночков. Тогда мои предки покинули побережье и стали жить на заболоченном острове посреди озера. Прошло время, и теночки сумели укрепить остров и даже построить дамбу к берегу. И когда теночки выбрали своим вождем Ицкоатля, была создана конфедерация племен, и народы конфедерации стали называться ацтеками.\n"+
				"Настали благословенные времена, ацтеки правили миром. Все племена платили ацтекам подати, поставляли еду, рабов и наложниц. Жертвенная кровь - пища наших богов - делала красным воды Тескоко. Знатных воинов приносили в жертву Тескатлипоке, покровителю жрецов, а в честь Камаштли обычных воинов сжигали. Женщины отдавали свою кровь богине Майяуэль, а дети - богу плодородия Тлалоку.\n"+
				"Так было больше ста лет. Но потом пришли испанцы и Теночтитлан попал в осаду. И пали наши герои во главе с Куаутемоком.\n"+
				"Теперь в Теночтитланом хозяйничает бог царства мертвых Миктлантекутли.";
			link.l1 = "Так что, город необитаем?";
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = "Обитаем. Там живут как живые люди, так и мертвые.";
			link.l1 = "Чего?";
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = "Миктлантекутли имеет власть воскрешать людей. Миктлантекутли вернул к жизни воинов для охраны храмов богов, а есть и живые ацтеки.";
			link.l1 = "А почему ты не живешь в Теночтитлане?";
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = "Меня изгнал Миктлантекутли. Пока власть его безгранична, я не могу вернуться\nСлушай меня, белый капитан. Сейчас я предложу тебе сделку, которую заключаю с каждым, кто приходит сюда.";
			link.l1 = "Я слушаю тебя, Монтесума.";
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = "Если ты сумеешь уменьшить власть Миктлантекутли, то я помогу тебе обрести могущество. В храме Белых Богов есть оружие, равного которому нет и не будет. Ты можешь забрать его себе.";
			link.l1 = "А что нужно тебе?";
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = "Нефритовый череп Миктлантекутли. Он находится в храме Великой Жизненной Силы.";
			link.l1 = "Я так понимаю, добраться туда будет непросто.";
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = "Я помогу тебе советом.";
			link.l1 = "А может, пойдем со мной в город? Будешь махать своей дубиной, раскалывать черепа...";
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = "Дубиной?! Сам ты дубина!\nЭто обсидиановый меч Макуауитль! Знаешь ли ты, что наши обсидиановые копья и мечи страшили испанцев больше, чем железные?";
			link.l1 = "Извини, Монтесума, за вопрос, но почему же вы тогда войну-то проиграли?";
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = "Наши боги отвернулись от нас...";
			link.l1 = "Опять боги...";
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = "Боги решают все, не люди. Один мой предок пытался решить все за богов, и он ошибся. Цена, заплаченная им за эту ошибку, была непомерно высокой.\nНу ладно, давай лучше поговорим о сделке. Ты согласен проникнуть в Теночтитлан и принести мне нефритовый череп?";
			link.l1 = "Я готов попробовать.";
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			dialog.text = "Хорошо. Тогда, для начала, тебе нужно снять заклятие огня с дамбы, ведущей в город.";
			link.l1 = "И как это сделать? Кто вообще смог такое организовать?";
			link.l1.go = "FT_19";
		break;
		case "FT_19":
			dialog.text = "Миктлантекутли, кто же еще? Силой Камаштли, бога войны и судьбы, он наложил на дамбу заклятие огня. Ибо Камаштли является творцом огня.";
			link.l1 = "Понятно... Ну, так как снять этот огонь?";
			link.l1.go = "FT_20";
		break;
		case "FT_20":
			dialog.text = "Есть два способа. Первый, это найти тотем Камаштли, пробраться сквозь огонь в город, и вставить этот Тотем в жертвенный камень, что находится недалеко от входа в город.";
			link.l1 = "Пробраться сквозь огонь? Так, я же сгорю!";
			link.l1.go = "FT_21";
		break;
		case "FT_21":
			dialog.text = "На деревянном перешейке дамбы огня нет. Ты сможешь там отдохнуть.";
			link.l1 = "Ясно... А второй способ?";
			link.l1.go = "FT_22";
		break;
		case "FT_22":
			dialog.text = "Найти два тотема - богини Тласолтеотль, пожирательницы грязи, и бога неба и солнца Тонатиу. Затем вставить их в жертвенные камни, что находятся на берегу перед дамбой. Тогда заклятие будет снято и ты сможешь спокойно пройти в Теночтитлан.";
			link.l1 = "Понятно. И где искать эти тотемы?";
			link.l1.go = "FT_23";
		break;
		case "FT_23":
			dialog.text = "Я не могу тебе это сказать, иначе наша сделка потеряет смысл\nНо могу намекнуть...";
			link.l1 = "Ну, намекай.";
			link.l1.go = "FT_24";
		break;
		case "FT_24":
			dialog.text = "Тотем Камаштли находится ближе, чем ты думаешь. Тотем Тласолтеотль находится недалеко, в траве. А тотем Тонатиу заброшен в джунгли между двумя испанскими городами, что расположены на перешейке между континентами.";
			link.l1 = "Черт! А точней никак нельзя?";
			link.l1.go = "FT_25";
		break;
		case "FT_25":
			dialog.text = "Никак. Ищи, белый капитан. Я все сказал, теперь дело за тобой.";
			link.l1 = "Ладно, буду искать...";
			link.l1.go = "exit";
			npchar.location.locator = "quest1";
			NextDiag.TempNode = "Fire";
			AddDialogExitQuestFunction("Teno_MontesumaGoQuest1");
		break;
		//--------------
		case "FTS_1":
			dialog.text = "Да, я ацтек, ты угадал. Меня зовут Монтесума. А как я могу называть тебя?";
			link.l1 = "Меня зовут капитан " + GetFullName(pchar) + ". Монтесума... Кажется, так звали индейского вождя.";
			link.l1.go = "FTS_2";
		break;
		case "FTS_2":
			dialog.text = "Я назван в его честь\nСкажи мне, белый капитан " + GetFullName(pchar) + ", что ты собираешься делать дальше? Ты ведь сумел снять заклятие огня!";
			link.l1 = "Обыщу как следует город. Возможно, найду что-нибудь стоящее.";
			link.l1.go = "FTS_3";
		break;
		case "FTS_3":
			dialog.text = "Я хочу сделать тебе предложение, белый капитан.";
			link.l1 = "Слушай тебя, Монтесума.";
			link.l1.go = "FTS_4";
		break;
		case "FTS_4":
			dialog.text = "Хорошо. Слушай вниматльено, белый капитан.\n"+
				"Мои предки пришли на берега этого озера, называемого Тескоко, много веков назад. Тогда их звали мешики. Берега озера были заселены другими племенами, которые враждебно отнеслись к пришельцам. Но наш верховный бог, Уицилопочтли, повелел им остаться здесь. Тогда вождь мешиков Теноч принял решение остаться на берегах Тескоко, а мешики стали называться теночками.\n"+
				"Кошкоштли, вождь могущественного города Кулуакана, замыслил истребить теночков. Тогда мои предки покинули побережье и стали жить на заболоченном острове посреди озера. Прошло время, и теночки сумели укрепить остров и построить каменный город и даже дамбу к берегу. И когда теночки выбрали своим вождем Ицкоатля, была создана конфедерация племен, и народы конфедерации стали называться ацтеками.\n"+
				"Настали благословенные времена, ацтеки правили миром. Все племена платили ацтекам подати, поставляли еду, рабов и наложниц. Жертвенная кровь - пища наших богов - делала красным воды Тескоко. Знатных воинов приносили в жертву Тескатлипоке, покровителю жрецов, а в честь Камаштли обычных воинов сжигали. Женщины отдавали свою кровь богине Майяуэль, а дети - богу плодородия Тлалоку.\n"+
				"Так было больше ста лет. Но потом пришли испанцы и Теночтитлан попал в осаду. И пали наши герои во главе с Куаутемоком.\n"+
				"Теперь в Теночтитланом хозяйничает бог царства мертвых Миктлантекутли.";
			link.l1 = "Так что, город необитаем?";
			link.l1.go = "FTS_5";
		break;
		case "FTS_5":
			dialog.text = "Обитаем. Там живут как живые люди, так и мертвые.";
			link.l1 = "Чего?";
			link.l1.go = "FTS_6";
		break;
		case "FTS_6":
			dialog.text = "Миктлантекутли имеет власть воскрешать людей. Миктлантекутли вернул к жизни воинов для охраны храмов богов, а есть и живые ацтеки.";
			link.l1 = "А почему ты не живешь в Теночтитлане?";
			link.l1.go = "FTS_7";
		break;
		case "FTS_7":
			dialog.text = "Меня изгнал Миктлантекутли. Пока власть его безгранична, я не могу вернуться\nСлушай меня, белый капитан. Сейчас я предложу тебе сделку, которую заключаю с каждым, кто приходит сюда.";
			link.l1 = "Я слушаю тебя, Монтесума.";
			link.l1.go = "FTS_8";
		break;
		case "FTS_8":
			dialog.text = "Если ты сумеешь уменьшить власть Миктлантекутли, то я помогу тебе обрести могущество. В храме Белых Богов есть оружие, равного которому нет и не будет. Ты можешь забрать его себе.";
			link.l1 = "А что нужно тебе?";
			link.l1.go = "FTS_9";
		break;
		case "FTS_9":
			dialog.text = "Нефритовый череп Миктлантекутли. Он находится в храме Великой Жизненной Силы.";
			link.l1 = "Я так понимаю, добраться туда будет непросто.";
			link.l1.go = "FTS_10";
		break;
		case "FTS_10":
			dialog.text = "Я помогу тебе советом.";
			link.l1 = "А может, пойдем со мной в город? Будешь махать своей дубиной, раскалывать черепа...";
			link.l1.go = "FTS_11";
		break;
		case "FTS_11":
			dialog.text = "Дубиной?! Сам ты дубина!\nЭто обсидиановый меч Макуауитль! Знаешь ли ты, что наши обсидиановые копья и мечи страшили испанцев больше, чем железные?";
			link.l1 = "Извини, Монтесума, за вопрос, но почему же вы тогда войну-то проиграли?";
			link.l1.go = "FTS_12";
		break;
		case "FTS_12":
			dialog.text = "Наши боги отвернулись от нас...";
			link.l1 = "Опять боги...";
			link.l1.go = "FTS_13";
		break;
		case "FTS_13":
			dialog.text = "Боги решают все, не люди. Один мой предок пытался решить все за богов, и он ошибся. Цена, заплаченная им за эту ошибку, была непомерно высокой.\nНу ладно, давай лучше поговорим о сделке. Ты согласен проникнуть в Теночтитлан и принести мне нефритовый череп?";
			link.l1 = "Я готов попробовать.";
			link.l1.go = "FTS_14";
		break;
		case "FTS_14":
			dialog.text = "Хорошо. Теперь слушай, что ты должен сделать.";
			link.l1 = "Слушаю тебя, Монтесума.";
			link.l1.go = "Fire_1";
		break;
		//после снятия огня
		case "Fire":
			if (CheckAttribute(loadedLocation, "gotoFire"))
			{
				dialog.text = "Заклятие огня еще не снято с дамбы.";
				link.l1 = "Пока нет, но я работаю над этим.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ты сумел снять заклятие огня, это хорошо. Теперь слушай, что ты должен сделать дальше.";
				link.l1 = "Слушаю внимательно, Монтесума.";
				link.l1.go = "Fire_1";
			}
		break;
		case "Fire_1":
			dialog.text = "Ты получил доступ в Теночтитлан и можешь заходить в храмы богов. Нефритовый череп, который мне нужен, находится в храме Великой Жизненной Силы. Чтобы получить туда доступ, ты должен собрать 10 тотемов богов и расставить их на жертвенные камни 10 храмов.";
			link.l1 = "И где эти храмы находятся?";
			link.l1.go = "Fire_2";
		break;
		case "Fire_2":
			dialog.text = "Пять в пирамиде слева от храма Великой Жизненной Силы, пять - справа от него же. В малых пирамидах есть пять входов, каждый из которых ведет в храм своего бога. Над каждым входом ты можешь увидеть изображение бога, которому и принадлежит данных храм. Смотреть лучше в полдень\nТебе нельзя ошибаться на входе, так как с каждым твоим посещением сила храмовой стражи будет расти.";
			link.l1 = "Там еще и храмовая стража имеется?";
			link.l1.go = "Fire_3";
		break;
		case "Fire_3":
			dialog.text = "Да, воскрешенные Миктлантекутли ацтекские войны. Тебе придется сражаться с ними. Внутрь храмов ты не сможешь взять помощников, так что все придется делать только тебе.";
			link.l1 = "М-да, плохая новость... А что за 10 тотемов я должен розыскать?";
			link.l1.go = "Fire_4";
		break;
		case "Fire_4":
			dialog.text = "Ты должен найти следующие тотемы: Шочикецаль, богини цветов и любви\nМиктлантекутли, уже известного тебе бога мертвых\nКецалькоатля, бога утренней звезды, владыки стихий\nМишкоатля, бога охоты\nТескатлипока, покровителя жрецов\nЧалчиуитликуэ, богини моря и озер\nУицилопочтли, бога голубого ясного неба\nУицилопочтли, бога грома и дождя\nМайяуэль, богини плодородия\nТонакатекутли, бога-созидателя, дарующего людям пищу.";
			link.l1 = "Понятно. А теперь намекни, где достать эти тотемы.";
			link.l1.go = "Fire_5";
		break;
		case "Fire_5":
			dialog.text = "Нет, этого я сделать не могу. Ищи их по всему миру сам.";
			link.l1 = "Отличная новость! Послушай, а не тебе ли нужен нефритовый череп? Что-то ты не очень проявляешь рвение в этом деле.";
			link.l1.go = "Fire_6";
		break;
		case "Fire_6":
			dialog.text = "Это все, что я могу. На все, что я делаю, есть свои причины, поверь мне.";
			link.l1 = "Понятно... Ну что же, тогда жди, когда я сумею раздобыть эти тотемы, проникнуть в храм и принести тебе череп. Боюсь, что ждать придется долго.";
			link.l1.go = "Fire_7";
		break;
		case "Fire_7":
			dialog.text = "Я буду ждать, белый капитан. Это единственное, что мне остается...";
			link.l1 = "Ну, тогда до встречи.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Totem";
			pchar.questTemp.Teno = "openTenTemples";
			AddQuestRecord("Tenochtitlan", "3");
		break;

		case "Totem":
			dialog.text = "У тебя нет нефритового черепа! Я жду, когда ты принесешь его мне, белый капитан.";
			link.l1 = "Я занимаюсь этим, Монтесума.";
			link.l1.go = "exit";
		break;

        //после драки с
		case "AfterGTemple":
			if (CheckCharacterItem(pchar, "SkullAztec")) //череп найден
			{
				dialog.text = "Ты добыл нефритовый череп Миктлантекутли! Отдай его мне!!!";
				if (CheckCharacterItem(pchar, "pistol7"))
				{
					link.l1 = "И что я за это получу? Он мне, знаешь ли, непросто достался...";
					link.l1.go = "Skull_1";
				}
				else
				{
					link.l1 = "Не так быстро, приятель! Ты обещал мне какое-то мощное оружие. Я так ничего и не нашел.";
					link.l1.go = "NotShootgun_1";
				}
			}
			else
			{
				dialog.text = "Ты был в Храме Великой Жизненной Силы. Но нефритового черепа у тебя нет с собой. Почему ты не взял его?";
				link.l1 = "Не нашел.";
				link.l1.go = "NotSkull";
			}
		break;
		//с собой нет черепа
		case "NotSkull":
			dialog.text = "Ты лжешь, белый капитан. За это Монтесума покарает тебя!";
			link.l1 = "Ну, попробуй...";
			link.l1.go = "NotSkull_1";
		break;
		case "NotSkull_1":
			chrDisableReloadToLocation = true;
			LAi_group_SetRelation("MontesumaGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("MontesumaGroup", LAI_GROUP_PLAYER, true);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NotShootgun_1":
			dialog.text = "Оружие находится в Храме Белых Богов, я же говорил тебе!";
			link.l1 = "Он закрыт.";
			link.l1.go = "NotShootgun_2";
		break;
		case "NotShootgun_2":
			dialog.text = "Храм открывает обсидиановый нож, которым жрецы сердце сердце у жертв. Найди его, и ты сумеешь открыть храм.";
			link.l1 = "А где его искать?";
			link.l1.go = "NotShootgun_3";
		break;
		case "NotShootgun_3":
			dialog.text = "В Храме Великой Жизненной Силы\nА теперь отдай мне череп!";
			link.l1 = "Одного указания на то, что оружие лежит в каком-то храме, мне мало. И что я еще могу получить ценного? Этот череп мне, знаешь ли, непросто достался...";
			link.l1.go = "Skull_1";
		break;

		case "Skull_1":
			dialog.text = "Ты смеешь мне перечить, несчастный?! Ты не знаешь, с кем говоришь!";
			link.l1 = "Знаю. Ты Монтесума Второй, последний правитель ацтеков. Это мне Миктлантекутли рассказал.";
			link.l1.go = "Skull_2";
		break;
		case "Skull_2":
			dialog.text = "Я последний раз прошу отдать мне нефритовый череп. Я помогал тебе получить его, мы договорились!";
			link.l1 = "А зачем он тебе?";
			link.l1.go = "Skull_3";
		break;
		case "Skull_3":
			dialog.text = "С его помощью я верну свой народ к жизни. Теночтитлан снова обретет могущество, и империя ацтеков покорит народы!";
			link.l1 = "Ваши боги отвернулись от ацтеков. А твоего народа больше нет.";
			link.l1.go = "Skull_4";
		break;
		case "Skull_4":
			dialog.text = "Я подниму свой народ из могил при помощи нефритового черепа! А богов мы найдем себе новых, задобрим их кровью рабов. Ацтеки вновь обретут силу, но теперь у нас будет и опыт. Ошибок прошлого я не повторю, и белые люди заплатят за свое коварство!";
			link.l1 = "Я не отдам тебе череп, Монтесума. Ты тут нарисовал картину, которая мне не нравится.";
			link.l1.go = "Skull_5";
		break;
		case "Skull_5":
			dialog.text = "Тогда готовься к смерти.";
			link.l1 = "Готовься и ты. Я выдержал схватку с самим Миктлантекутли, а уж тебя-то точно отправлю к нему на постоянное место жительства.";
			link.l1.go = "Skull_6";
		break;
		case "Skull_6":
			dialog.text = "Я не могу умереть второй раз, белый капитан!";
			link.l1 = "У меня есть нефритовый череп, а он дает власть над мертвыми. Значит, и над тобой. Полагаю, что это все меняет.";
			link.l1.go = "Skull_7";
		break;
		case "Skull_7":
			AddQuestRecord("Tenochtitlan", "5");
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Tenochtitlan", "reload1_back", false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "MontesumaGroup");
			LAi_group_SetRelation("MontesumaGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("MontesumaGroup", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("MontesumaGroup", "OpenTheDoors");
			pchar.quest.Teno_clearGroups.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Teno_clearGroups.win_condition.l1.location = pchar.location;
			pchar.quest.Teno_clearGroups.function = "Teno_clearGroups";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

	}
}
